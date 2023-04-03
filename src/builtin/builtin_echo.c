/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:09:05 by dpalmer           #+#    #+#             */
/*   Updated: 2023/04/03 12:14:41 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"

int	builtin_echo(t_vector *argv)
{
	size_t	index;
	BOOL	n_flag;

	index = 1;
	n_flag = FALSE;
	if (argv->length < 2)
	{
		printf("\n");
		return (OK);
	}
	if (!ft_strncmp(*(char **)vector_get(argv, 1), "-n", 2))
	{
		n_flag = TRUE;
		index++;
	}
	if (index < argv->length)
		printf("%s", *(char **)vector_get(argv, index++));
	while (index < argv->length)
		printf(" %s", *(char **)vector_get(argv, index++));
	if (!n_flag)
		printf("\n");
	return (OK);
}
