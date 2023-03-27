/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:34:52 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/27 13:40:05 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "builtin.h"

int	builtin_pwd(t_vector *argv)
{
	char	cwd[4096];

	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
		perror("minishell: cd");
	printf("%s\n", cwd);
	return (OK);
}
