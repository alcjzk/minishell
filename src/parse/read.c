/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:35:38 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/15 12:22:58 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

// TODO: Behavior of unknown metacharacters?

BOOL	read_word(const char *input, size_t *index, t_token *token)
{
	size_t	length;

	token->type = token_type_word;
	length = wordspan(&input[*index]);
	if (!length)
		return (FALSE);
	token->word = ft_substr(input, *index, length);
	if (!token->word)
		return (FALSE);
	(*index) += length;
	return (TRUE);
}

BOOL	read_operator(const char *input, size_t *index, t_token *token)
{
	token->type = token_type_operator;
	if (input[*index] == '|')
		token->operator = operator_pipe;
	else if (input[*index] == '<')
		token->operator = operator_infile;
	else if (input[*index] == '>')
		token->operator = operator_outfile_truncate;
	else
		return (FALSE);
	if (input[*index] == input[*index + 1])
	{
		token->operator += 1;
		(*index)++;
	}
	(*index)++;
	return (TRUE);
}

BOOL	read_line_quotes(char *line)
{
	int		flags;
	size_t	index;

	flags = 0;
	index = 0;
	while (line[index])
	{
		if (line[index] == '\'' && !(flags & D_QUOTE))
			flags ^= S_QUOTE;
		else if (line[index] == '\"' && !(flags & S_QUOTE))
			flags ^= D_QUOTE;
		index++;
	}
	if ((flags & D_QUOTE) || (flags & S_QUOTE))
		return (FALSE);
	return (TRUE);
}
