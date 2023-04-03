/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:27:38 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/04/03 12:40:15 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "bool.h"
# include "vector.h"

# define BUILTINS_LENGTH 7
///	Ok.
# define OK 0
///	Builtin was not found.
# define ERR_NOT_FOUND 1
///	Builtin was given an incorrect number of / invalid arguments.
# define ERR_INVALID_ARGS 2
/// System errors
# define ERR_SYSTEM 3
/// Buffer for PWD
# define PWD_BUFF 4096

typedef int	(*t_builtin_func)(t_vector *);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

t_builtin_func	builtin_get(char *name);
int				builtin_exec(t_vector *argv);
int				builtin_echo(t_vector *argv);
int				builtin_cd(t_vector *argv);
int				builtin_pwd(t_vector *argv);
int				builtin_export(t_vector *argv);
int				builtin_unset(t_vector *argv);
int				builtin_env(t_vector *argv);
int				builtin_exit(t_vector *argv);

#endif
