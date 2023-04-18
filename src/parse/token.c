/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:14:36 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/04/18 11:54:47 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"
#include "libft.h"
#include "parse.h"

static BOOL	_tokenize(char *line, t_vector *tokens);

t_token	token_from_word(t_word word)
{
	t_token	token;

	token.type = token_type_word;
	token.word = word;
	return (token);
}

t_token	token_from_operator(t_operator operator)
{
	t_token	token;

	token.type = token_type_operator;
	token.operator = operator;
	return (token);
}

static BOOL	_tokenize(char *line, t_vector *tokens)
{
	size_t	index;
	t_token	token;

	index = 0;
	while (TRUE)
	{
		index += ft_strspn(&line[index], CHARSET_DELIM);
		if (!line[index])
			break ;
		if (ft_strchr(CHARSET_META, line[index]))
		{
			if (!read_operator(line, &index, &token))
				return (FALSE);
		}
		else
		{
			if (!read_word(line, &index, &token))
				return (FALSE);
		}
		if (!vector_push(tokens, &token))
			return (FALSE);
	}
	return (TRUE);
}

t_vector	*tokenize(char *line)
{
	t_vector		*tokens;

	tokens = vector_with_capacity(1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	if (!_tokenize(line, tokens))
	{
		tokens_free(tokens);
		return (NULL);
	}
	return (tokens);
}

void	tokens_free(t_vector *tokens)
{
	size_t	index;
	t_token	*token;

	index = 0;
	while (index < tokens->length)
	{
		token = vector_get(tokens, index);
		if (token->type == token_type_word)
			free(token->word);
		index++;
	}
	vector_free(tokens);
}
