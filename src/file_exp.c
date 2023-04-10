/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:18:42 by dpalmer           #+#    #+#             */
/*   Updated: 2023/04/10 12:06:04 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "main.h"
#include "vector.h"
#include "bool.h"

static BOOL	_pattern_match(
	const char *pattern,
	const char *string,
	int idx_pat,
	int idx_str)
{
	if (pattern[idx_pat] == '\0')
		return (string[idx_str] == '\0');
	else if (pattern[idx_pat] == '*')
	{
		while (string[idx_str] != '\0')
		{
			if (_pattern_match(pattern, string, idx_pat + 1, idx_str))
				return (TRUE);
			idx_str++;
		}
		return (_pattern_match(pattern, string, idx_pat + 1, idx_str));
	}
	else if (pattern[idx_pat] != string[idx_str])
		return (FALSE);
	else
		return (_pattern_match(pattern, string, idx_pat + 1, idx_str + 1));
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

	matches = vector_with_capacity(1, sizeof(char *));
	if (!matches)
		return (NULL);
	dirp = opendir(".");
	if (!dirp)
	{
		vector_free(matches);
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
