/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:07:29 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/04/05 14:27:23 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "shell.h"

t_shell	g_shell;

void	shell_init(char **envp)
{
	env_init(envp);
	signal(SIGINT, handle_int);
	signal(SIGQUIT, SIG_IGN);
}

void	free_shell(void)
{
	if (g_shell.line)
		free(g_shell.line);
	env_free();
}

void	handle_int(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
