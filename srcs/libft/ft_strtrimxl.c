/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimxl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 02:14:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/23 01:19:49 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;
	size_t	str_size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = ft_strfind_start(s1, set);
	end = ft_strfind_end(s1, set);
	if (start >= end)
		str_size = 0;
	else
		str_size = end - start;
	if ((str = (char*)malloc((str_size) + 1)))
	{
		ft_memmove(str, s1 + start, str_size);
		str[str_size] = '\0';
		if (s1)
			free(s1);
		return (str);
	}
	return (NULL);
}
