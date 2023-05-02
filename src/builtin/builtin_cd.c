/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:38:38 by dpalmer           #+#    #+#             */
/*   Updated: 2023/05/02 13:16:57 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"
#include "ft.h"
#include "env.h"

static int	_error(void)
{
	perror ("minishell: cd");
	return (EXIT_FAILURE);
}

static const char	*parse_path(t_vector *argv)
{
	const char	*path;

	if (argv->length <= 1 || **(char **)vector_get(argv, 1) == '\0')
		path = env_get("HOME");
	else
		path = *(char **)vector_get(argv, 1);
	return (path);
}

static int	_builtin_cd(const char *to)
{
	char	buffer[PATH_BUFFER_SIZE];

	if (!getcwd(buffer, PATH_BUFFER_SIZE))
		return (_error());
	if (chdir(to) == -1)
		return (_error());
	if (!env_set("OLDPWD", buffer))
		return (_error());
	if (!env_set("PWD", getcwd(buffer, PATH_BUFFER_SIZE)))
		return (_error());
	return (OK);
}

int	builtin_cd(t_vector *argv)
{
	const char	*to;

	to = parse_path(argv);
	if (!to)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(to, "-", 1) == 0)
	{
		to = env_get("OLDPWD");
		if (to)
			printf("%s\n", to);
	}
	return (_builtin_cd(to));
}
