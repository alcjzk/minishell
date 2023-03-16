/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:36:14 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/03/16 11:37:35 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

BOOL	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (TRUE);
	return (FALSE);
}
