/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:09:05 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/31 11:34:38 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "builtin.h"
#include <stdio.h>

int	builtin_echo(t_vector *argv)
{
	const char	*string;
	size_t		index;
	BOOL		n_flag;

	index = 1;
	n_flag = FALSE;
	if (!ft_strncmp(*(char **)vector_get(argv, 1), "-n", 2))
	{
		n_flag = TRUE;
		index++;
	}
	while (index < argv->length)
	{
		string = *(char **)vector_get(argv, index);
		write(STDOUT_FILENO, string, ft_strlen(string));
		if (index < argv->length && string[0] != '\0')
			write(STDOUT_FILENO, " ", 1);
		index++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (OK);
}
