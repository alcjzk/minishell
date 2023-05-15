/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:32:51 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/15 12:06:43 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft.h"
#include "str.h"
#include "shell.h"
#include "parse.h"

#define AL_NUM "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

static BOOL	word_expand_var(
				const t_word self,
				t_str *str,
				size_t *index,
				const t_env *env);
static BOOL	word_expand_vars_unquoted(
				const t_word word,
				t_str *str,
				const t_env *env);
static BOOL	word_expand_vars_quoted(
				const t_word word,
				t_str *str,
				const t_env *env);

t_word	word_expand_vars(const t_word self, BOOL ign_quotes, const t_env *env)
{
	t_str	*str;
	BOOL	ok;

	str = str_from_ptr("");
	if (!str)
		return (NULL);
	if (ign_quotes)
		ok = word_expand_vars_unquoted(self, str, env);
	else
		ok = word_expand_vars_quoted(self, str, env);
	if (ok)
		return (str_as_ptr(str));
	str_free(str);
	return (NULL);
}

static BOOL	word_expand_var(
	const t_word self,
	t_str *str,
	size_t *index,
	const t_env *env)
{
	const char	*value;
	char		*tmp;

	if (self[++(*index)] == '?')
	{
		tmp = ft_itoa(g_shell.status);
		if (!str_push_ptr(str, tmp))
			return (FALSE);
		free(tmp);
	}
	else if (self[*index] == '_' || ft_isalpha(self[*index]))
	{
		tmp = ft_substr(self, *index, ft_strspn(&self[*index], AL_NUM));
		if (!tmp)
			return (FALSE);
		value = env_get(env, tmp);
		if (value && !str_push_ptr(str, value))
			return (FALSE);
		free(tmp);
		(*index) += ft_strspn(&self[*index], AL_NUM) - 1;
	}
	else if (!str_push(str, '$'))
		return (FALSE);
	return (TRUE);
}

static BOOL	word_expand_vars_unquoted(
	const t_word word,
	t_str *str,
	const t_env *env)
{
	ssize_t	index;

	index = -1;
	while (word[++index])
	{
		if (word[index] == '$')
		{
			if (!word_expand_var(word, str, (size_t *)&index, env))
				return (FALSE);
		}
		else if (!str_push(str, word[index]))
			return (FALSE);
	}
	return (TRUE);
}

static BOOL	word_expand_vars_quoted(
	const t_word word,
	t_str *str,
	const t_env *env)
{
	char	flags;
	ssize_t	index;

	flags = 0;
	index = -1;
	while (word[++index])
	{
		if (word[index] == '$' && !(flags & S_QUOTE))
		{
			if (!word_expand_var(word, str, (size_t *)&index, env))
				return (FALSE);
		}
		else
		{
			if (word[index] == '\'' && !(flags & D_QUOTE))
				flags ^= S_QUOTE;
			else if (word[index] == '\"' && !(flags & S_QUOTE))
				flags ^= D_QUOTE;
			else if (!str_push(str, word[index]))
				return (FALSE);
		}
	}
	return (TRUE);
}
