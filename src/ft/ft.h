/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:36:26 by tjaasalo          #+#    #+#             */
/*   Updated: 2023/05/25 12:35:16 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stddef.h>
# include "bool.h"

# define ERR_INVALID "The string did not consist solely of digit characters."
# define ERR_TOOSMALL "The result was smaller than the provided minimum value."
# define ERR_TOOLARGE "The result was larger than the provided maximum value."

BOOL		ft_isspace(char c);
size_t		ft_strspn(const char *str, const char *charset);
size_t		ft_strcspn(const char *str, const char *charset);
long long	ft_strtonum(
				const char *str,
				long long min,
				long long max,
				const char **errstr);
char		*ft_strtok(char *restrict str, const char *restrict delim);

#endif
