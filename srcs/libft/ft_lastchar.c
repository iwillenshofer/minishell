/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 17:23:35 by fde-capu          #+#    #+#             */
/*   Updated: 2020/04/22 17:23:56 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lastchar(char *str)
{
	if ((!str) || (!*str))
		return (str);
	while (*str)
	{
		if (!*(str + 1))
			return (str);
		str++;
	}
	return (str);
}
