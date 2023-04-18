/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:14:36 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/04/18 11:39:16 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "bool.h"
#include "ft.h"
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

size_t	wordspan(char *input)
{
	size_t	index;

	index = 0;
	while (input[index])
	{
		index += ft_strcspn(&input[index], CHARSET_QUOT_DELIM_META);
		if (input[index] == '\'')
		{
			index++;
			index += ft_strcspn(&input[index], "\'");
			if (input[index++] != '\'')
				return (0);
		}
		else if (input[index] == '\"')
		{
			index++;
			index += ft_strcspn(&input[index], "\"");
			if (input[index++] != '\"')
				return (0);
		}
		else
			return (index);
	}
	return (index);
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

void	print_tokens(t_vector *tokens)
{
	t_token	*token;

	printf("tokens : %zu\n", tokens->length);
	for (size_t i = 0; i < tokens->length; i++)
	{
		token = vector_get(tokens, i);
		// printf("index: %zu | %p\n", i, token);
		if (token->type == token_type_operator)
		{
			printf("OPERATOR %i\n", token->operator);
		}
		else
		{
			printf("WORD: %s\n", token->word);
		}
	}
}