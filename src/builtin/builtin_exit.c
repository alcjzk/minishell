/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:27:19 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/23 10:44:38 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft.h"
#include "shell.h"
#include "error.h"
#include "builtin.h"

static int	int_max(void)
{
	return ((int)(((unsigned int)-1) / 2));
}

static int	int_min(void)
{
	return ((int)(((((unsigned int)-1) / 2) + 1)));
}

int	builtin_exit(t_vector *argv, t_env *env)
{
	const char	*err_str;
	int			exit_code;
	char		*arg;

	(void)env;
	err_str = NULL;
	write(STDERR_FILENO, "exit\n", 5);
	if (!argv || argv->length <= 1)
		exit_code = g_shell.status;
	else
	{
		arg = *(char **)vector_get(argv, 1);
		exit_code = ft_strtonum(arg, int_min(), int_max(), &err_str);
		if (err_str)
		{
			exit_code = EXIT_FAILURE | EXIT_FATAL;
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
		}
	}
	exit (exit_code | EXIT_FATAL);
	return (0);
}
