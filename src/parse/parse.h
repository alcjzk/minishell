/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:14:19 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/25 13:39:11 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define CHARSET_DELIM " "
# define CHARSET_QUOT_DELIM_META "\'\" |<>"
# define CHARSET_DELIM_META " |<>"
# define CHARSET_META "|<>"

# include <fcntl.h>
# include "bool.h"
# include "builtin.h"
# include "vector.h"

typedef enum e_token_type
{
	token_type_operator,
	token_type_word
}	t_token_type;

typedef enum e_operator
{
	operator_pipe,
	operator_or,
	operator_outfile_truncate,
	operator_outfile_append,
	operator_infile,
	operator_heredoc
}	t_operator;

typedef char		*t_word;
/// A collection of tokens.
typedef t_vector	t_tokens;

typedef struct s_token
{
	t_token_type	type;
	union {
		t_word		word;
		t_operator	operator;
	};
}	t_token;

///	An iterator over tokens.
typedef struct s_tokens_iter
{
	t_tokens	*tokens;
	size_t		index;
}	t_tokens_iter;

typedef struct s_parser
{
	t_tokens	*tokens;
	t_vector	*commands;
}	t_parser;

int			tokenize(const char *line, t_tokens **tokens);
void		tokens_free(t_tokens *tokens);

///			Initializes the iterator.
///
///			@param iterator Non-null pointer to an iterator struct.
///			@param tokens Non-null pointer to a vector of tokens.
void		tokens_iter(t_tokens_iter *iterator, t_tokens *tokens);

///			Returns the next token from the collection if any and advances the
///			iterator.
///
///			@param iterator Non-null pointer to an initialized iterator.
///
///			@return A pointer to the next token in the collection. NULL if the
///			iterator is exhausted.
t_token		*tokens_next(t_tokens_iter *iterator);

/* Token internals */
t_token		token_from_operator(t_operator operator);
t_token		token_from_word(t_word word);
size_t		wordspan(const char *input);
/* Token internals */

int			read_word(const char *input, size_t *index, t_token *token);
int			read_operator(const char *input, size_t *index, t_token *token);

int			tokens_expand(t_tokens **self, const t_env *env);
t_tokens	*token_filenames(const char *pattern);
int			tokens_validate(const t_tokens *tokens);

t_word		word_expand_vars(
				const t_word self,
				BOOL ignore_quotes,
				const t_env *env);

// FIXME: Remove debug function
void		token_debug(t_token *token);
// FIXME: Remove debug function
void		tokens_debug(t_vector *tokens);

t_vector	*parser_commands(t_parser *self);
int			parse(const char *line, const t_env *env, t_vector **commands);

#endif
