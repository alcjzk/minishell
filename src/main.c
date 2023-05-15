/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:10:20 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/15 12:29:39 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "builtin.h"
#include "libft.h"
#include "ft.h"
#include "shell.h"
#include "vector.h"
#include "bool.h"
#include "parse.h"
#include "command.h"
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include "main.h"

char	*prompt(t_state *state)
{
	char	*line;

	termios_echoctl_disable(state->termios_state);
	line = readline("minishell> ");
	termios_echoctl_reset(state->termios_state);
	if (!read_line_quotes(line))
		write(STDERR_FILENO, "minishell: syntax error\n", 24);
	return (line);
}

BOOL	_parse(t_state *state, t_parser *parser)
{
	if (!parser->line)
	{
		g_shell.status = EXIT;
		return (FALSE);
	}
	if (!*parser->line)
		return (TRUE);
	add_history(parser->line);
	parser->tokens = tokenize(parser->line);
	if (!parser->tokens)
		return (FALSE);
	if (!tokens_expand(&parser->tokens, state->env))
		return (FALSE);
	parser->commands = commands_from_tokens(parser->tokens);
	if (!parser->commands)
		return (FALSE);
	if (!commands_init(parser->tokens, parser->commands))
		return (FALSE);
	return (TRUE);
}

t_vector	*parse(t_state *state, char *line)
{
	t_parser	parser;
	BOOL		ok;

	parser = (t_parser){0};
	parser.line = line;
	ok = _parse(state, &parser);
	if (parser.line)
		free(parser.line);
	if (parser.tokens)
		tokens_free(parser.tokens);
	if (!ok)
	{
		if (parser.commands)
			commands_free(parser.commands);
		return (NULL);
	}
	return (parser.commands);
}

// TODO: Does this function need a return value? Do something if exec fails?
BOOL	run(t_state *state)
{
	t_vector	*commands;

	commands = parse(state, prompt(state));
	if (!commands)
		return (FALSE);
	if (commands_exec(commands, state->env))
		g_shell.status = commands_status(commands);
	commands_free(commands);
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	(void)argc;
	(void)argv;
	if (!state_init(&state, envp))
		return (g_shell.status);
	while (1)
	{
		run(&state);
		if (g_shell.status & EXIT)
			break ;
	}
	state_free(&state);
	rl_clear_history();
	return (g_shell.status & (~EXIT));
}
