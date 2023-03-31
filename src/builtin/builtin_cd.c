/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:38:38 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/31 11:02:20 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"
#include "ft.h"
#include "env.h"

static const char	*parse_path(t_vector *argv)
{
	const char	*path;

	if (argv->length <= 1 || **(char **)vector_get(argv, 1) == '\0')
		path = env_get("HOME");
	else
		path = *(char **)vector_get(argv, 1);
	return (path);
}

static int	_builtin_cd(const char *to, const char *from)
{
	char	pwd_buff[4096];

	if (chdir(to) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	if (!getcwd(pwd_buff, 4096) || !env_set("OLDPWD", from)
		|| !env_set("PWD", pwd_buff))
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (OK);
}

int	builtin_cd(t_vector *argv)
{
	const char	*from;
	const char	*to;

	to = parse_path(argv);
	if (!to)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		return (EXIT_FAILURE);
	}
	from = env_get("PWD");
	if (ft_strncmp(to, "-", 1) == 0)
	{
		to = env_get("OLDPWD");
		if (to)
			printf("%s\n", to);
	}
	return (_builtin_cd(to, from));
}
