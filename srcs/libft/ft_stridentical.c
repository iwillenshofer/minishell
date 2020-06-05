/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stridentical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:50:46 by fde-capu          #+#    #+#             */
/*   Updated: 2020/04/22 21:04:17 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stridentical(const char *s1, const char *s2)
{
	char	*a;
	char	*b;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	a = (char *)s1;
	b = (char *)s2;
	while (a && b && *a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	return (!*a && !*b ? 1 : 0);
}
