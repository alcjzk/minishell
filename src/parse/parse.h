/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:14:19 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/16 12:06:53 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define CHARSET_DELIM " "
# define CHARSET_QUOT_DELIM_META "\'\" |<>"
# define CHARSET_DELIM_META " |<>"
# define CHARSET_META "|<>()"
# define D_QUOTE 0b01
# define S_QUOTE 0b10

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

///			Constructs a collection of tokens from a command line. The returned
///			value must be freed with `tokens_free`.
///
///			@param line Non-null command line.
///
///			@return A collection of tokens or NULL on error.
t_tokens	*tokenize(const char *line);

///			Frees the collection.
///
///			@param tokens The collection to be freed.
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

BOOL		read_word(const char *input, size_t *index, t_token *token);
BOOL		read_operator(const char *input, size_t *index, t_token *token);

BOOL		tokens_expand(t_tokens **self, const t_env *env);
t_tokens	*token_filenames(const char *pattern);
BOOL		tokens_validate(const t_tokens *tokens);

t_word		word_expand_vars(
				const t_word self,
				BOOL ignore_quotes,
				const t_env *env);

// FIXME: Remove debug function
void		token_debug(t_token *token);
// FIXME: Remove debug function
void		tokens_debug(t_vector *tokens);

#endif
