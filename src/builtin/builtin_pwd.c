/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:34:52 by dpalmer           #+#    #+#             */
/*   Updated: 2023/04/03 12:43:33 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"

int	builtin_pwd(t_vector *argv)
{
	char	cwd[PWD_BUFF];

	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (OK);
}
