/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:20:03 by dpalmer           #+#    #+#             */
/*   Updated: 2023/05/15 12:10:23 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include "ft.h"
#include "env.h"
#include "shell.h"
#include "parse.h"
#include "str.h"

static BOOL	_tokens_expand(
				const t_tokens *self,
				t_tokens *result,
				const t_env *env);
static BOOL	should_expand_filename(const t_word word);
static BOOL	token_expand_filename(
				const t_token *self,
				t_tokens *tokens,
				const t_env *env);
static BOOL	token_expand_variables(
				const t_token *self,
				t_tokens *tokens,
				const t_env *env);

BOOL	tokens_expand(t_tokens **self, const t_env *env)
{
	t_tokens	*result;
	t_tokens	*tmp;

	result = vector_with_capacity((*self)->length, sizeof(t_token));
	if (!result)
		return (FALSE);
	if (!_tokens_expand(*self, result, env))
	{
		tokens_free(result);
		return (FALSE);
	}
	tmp = *self;
	*self = result;
	tokens_free(tmp);
	return (TRUE);
}

static BOOL	_tokens_expand(
	const t_tokens *self,
	t_tokens *result,
	const t_env *env)
{
	size_t		index;
	t_token		*token;

	index = 0;
	while (index < self->length)
	{
		token = vector_get(self, index++);
		if (token->type == token_type_word)
		{
			if (should_expand_filename(token->word))
			{
				if (!token_expand_filename(token, result, env))
					return (FALSE);
			}
			else if (!token_expand_variables(token, result, env))
				return (FALSE);
		}
		else if (!vector_push(result, token))
			return (FALSE);
	}
	return (TRUE);
}

static BOOL	token_expand_filename(
	const t_token *self,
	t_tokens *tokens,
	const t_env *env)
{
	t_word		word;
	t_tokens	*filenames;

	word = word_expand_vars(self->word, TRUE, env);
	if (!word)
		return (FALSE);
	filenames = token_filenames(word);
	free(word);
	if (!filenames)
		return (FALSE);
	if (vector_extend(tokens, filenames))
		return (TRUE);
	tokens_free(filenames);
	return (FALSE);
}

static BOOL	token_expand_variables(
	const t_token *self,
	t_tokens *tokens,
	const t_env *env)
{
	t_token	token;

	token.type = token_type_word;
	token.word = word_expand_vars(self->word, FALSE, env);
	if (!token.word)
		return (FALSE);
	if (vector_push(tokens, &token))
		return (TRUE);
	free(token.word);
	return (FALSE);
}

static BOOL	should_expand_filename(const t_word word)
{
	size_t	index;
	BOOL	has_wildcard;

	index = 0;
	has_wildcard = FALSE;
	while (word[index])
	{
		if (word[index] == '\'' || word[index] == '\"')
			return (FALSE);
		if (word[index] == '*')
			has_wildcard = TRUE;
		index++;
	}
	return (has_wildcard);
}
