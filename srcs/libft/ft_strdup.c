/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:13:44 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/13 15:54:34 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	tot_bytes;
	char	*mem;

	tot_bytes = ft_strlen(s1) + 1;
	i = 0;
	if (!(mem = (char*)malloc(sizeof(char) * tot_bytes)))
		return (NULL);
	while (i < tot_bytes)
	{
		mem[i] = s1[i];
		i++;
	}
	return (mem);
}
