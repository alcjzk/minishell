/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:14:19 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/04/18 11:53:19 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define CHARSET_DELIM " "
# define CHARSET_QUOT_DELIM_META "\'\" |<>"
# define CHARSET_DELIM_META " |<>"
# define CHARSET_META "|<>()"

# include "bool.h"
# include "vector.h"

typedef enum e_token_type
{
	token_type_operator,
	token_type_word
}	t_token_type;

typedef enum e_operator
{
	pipe,
	or,
	outfile_truncate,
	outfile_append,
	infile,
	heredoc
}	t_operator;

typedef char	*t_word;

typedef struct s_token
{
	t_token_type	type;
	union {
		t_word		word;
		t_operator	operator;
	};
}	t_token;

BOOL		read_word(char *input, size_t *index, t_token *token);
BOOL		read_operator(char *input, size_t *index, t_token *token);

t_token		token_from_operator(t_operator operator);
t_token		token_from_word(t_word word);
void		tokens_free(t_vector *tokens);
t_vector	*tokenize(char *line);
size_t		wordspan(char *input);

#endif