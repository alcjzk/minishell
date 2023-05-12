/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:00:17 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/11 05:10:53 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "parse.h"

static BOOL	_tokens_validate(const t_tokens *tokens);
static BOOL	validate_first(const t_token *token);
static BOOL	validate_operator(
				const t_operator operator,
				const t_token *previous);

BOOL	tokens_validate(const t_tokens *tokens)
{
	if (_tokens_validate(tokens))
		return (TRUE);
	g_shell.status = ERR_SYNTAX;
	return (FALSE);
}

static BOOL	_tokens_validate(const t_tokens *tokens)
{
	size_t	index;
	t_token	*head;
	t_token	*previous;

	index = 0;
	previous = NULL;
	if (tokens->length < 1)
		return (TRUE);
	head = vector_get(tokens, index++);
	if (!validate_first(head))
		return (FALSE);
	while (index < tokens->length)
	{
		head = vector_get(tokens, index++);
		if (head->type == token_type_word)
			continue ;
		if (!validate_operator(head->operator, previous))
			return (FALSE);
		previous = head;
	}
	if (head->type == token_type_operator)
		return (FALSE);
	return (TRUE);
}

static BOOL	validate_first(const t_token *token)
{
	if (token->type == token_type_word)
		return (TRUE);
	if (token->operator == operator_or || token->operator == operator_pipe)
		return (FALSE);
	return (TRUE);
}

static BOOL	validate_operator(
	const t_operator operator,
	const t_token *previous)
{
	if (operator == operator_or)
		return (FALSE);
	if (previous && previous->type == token_type_operator)
	{
		if (previous->operator != operator_pipe)
			return (FALSE);
		if (operator == operator_pipe)
			return (FALSE);
	}
	return (TRUE);
}
