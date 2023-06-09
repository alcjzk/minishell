/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 07:49:08 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:10 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "util.h"
#include "command.h"

static void	command_exec_builtin(t_command *self, t_env *env);
static void	command_exec_external(t_command *self, const t_env *env);
static void	_command_exec_external(t_command *self, char **argv, char **envp);

void	command_exec_external(t_command *self, const t_env *env)
{
	pid_t		pid;
	char		**argv;
	char		**envp;

	if (!command_resolve(self, env))
		return ;
	envp = envp_from_env(env);
	argv = argv_from_vector(&self->args);
	pid = fork();
	if (pid == 0)
		_command_exec_external(self, argv, envp);
	close_safe(&self->input_fd);
	close_safe(&self->output_fd);
	argv_free(argv);
	argv_free(envp);
	if (pid > 0)
	{
		self->pid = pid;
		return ;
	}
	perror("minishell");
	return ;
}

static void	_command_exec_external(t_command *self, char **argv, char **envp)
{
	struct sigaction	action;

	if (!argv || !envp)
		return ;
	action.sa_handler = SIG_DFL;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGQUIT, &action, NULL);
	command_redirect(self);
	execve(self->name.value, argv, envp);
	return ;
}

void	command_exec_builtin(t_command *self, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		self->pid = pid;
		close_safe(&self->input_fd);
		close_safe(&self->output_fd);
		return ;
	}
	if (pid == 0)
	{
		command_redirect(self);
		self->status = self->builtin(self->args, env);
		exit(self->status);
	}
	perror("minishell");
}

void	commands_exec(t_vector *commands, t_env *env)
{
	size_t		index;
	t_command	*command;

	index = 0;
	if (commands->length == 1)
	{
		command = vector_get(commands, 0);
		if (command->builtin)
			command_run_builtin(command, env);
		else
			command_exec_external(command, env);
		return ;
	}
	while (index < commands->length)
	{
		command = vector_get(commands, index);
		if (command->builtin)
			command_exec_builtin(command, env);
		else
			command_exec_external(command, env);
		index++;
	}
}
