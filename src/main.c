/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:10:20 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/03/15 14:42:36 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "builtin.h"
#include "libft.h"
#include "main.h"

int	main(void)
{
	while (1)
	{
		g_line = readline(">");
		exec_builtin(g_line, NULL);
		free(g_line);
	}
	return (0);
}

BOOL	exec_builtin(char *cmd, char **argv)
{
	if (ft_strncmp("exit", cmd, 5) == 0)
		builtin_exit(argv);
	else if (ft_strncmp("env", cmd, 4) == 0)
		builtin_env(argv);
	else
		return (FALSE);
	return (TRUE);
}
