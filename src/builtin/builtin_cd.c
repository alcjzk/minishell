/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:38:38 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/27 13:52:00 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"
#include "ft.h"
#include "env.h"

int	builtin_cd(t_vector *argv)
{
	const char	*path;
	char		pwd_buff[4096];

	if (argv->length <= 1 || **(char **)vector_get(argv, 1) == '\0')
	{
		path = env_get("HOME");
		if (!path)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			return (EXIT_FAILURE);
		}
		path = &path[5];
	}
	else
		path = *(char **)vector_get(argv, 1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	if (!getcwd(pwd_buff, 4096) || !env_set("PWD", pwd_buff))
		perror("minishell: cd");
	return (OK);
}
