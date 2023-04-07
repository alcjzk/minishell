/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:18:42 by dpalmer           #+#    #+#             */
/*   Updated: 2023/04/07 14:49:57 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "main.h"
#include "vector.h"
#include "bool.h"

static BOOL	_pattern_match(const char *pattern,
	const char *string, int p, int s)
{
	if (pattern[p] == '\0')
		return (string[s] == '\0');
	else if (pattern[p] == '*')
	{
		while (string[s] != '\0')
		{
			if (_pattern_match(pattern, string, p + 1, s))
				return (TRUE);
			s++;
		}
		return (_pattern_match(pattern, string, p + 1, s));
	}
	else if (pattern[p] != string[s])
		return (FALSE);
	else
		return (_pattern_match(pattern, string, p + 1, s + 1));
}

BOOL	pattern_match(const char *pattern, const char *string)
{
	return (_pattern_match(pattern, string, 0, 0));
}

static t_vector	*files_try_push(t_vector *matches, char *pattern, char *string)
{
	if (pattern_match(pattern, string))
	{
		if (!vector_push(matches, &string))
		{
			vector_free(matches);
			return (NULL);
		}
	}
	return (matches);
}

t_vector	*filename_expansion(char *pattern)
{
	DIR				*dirp;
	t_vector		*matches;
	struct dirent	*dirent;

	matches = balls(1, sizeof(char *));
	if (!matches)
		return (NULL);
	dirp = opendir(".");
	if (!dirp)
	{
		perror("minishell");
		return (NULL);
	}
	dirent = readdir(dirp);
	while (dirent && matches)
	{
		matches = files_try_push(matches, pattern, dirent->d_name);
		dirent = readdir(dirp);
	}
	closedir(dirp);
	return (matches);
}
