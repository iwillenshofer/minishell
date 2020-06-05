/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 11:29:05 by fde-capu          #+#    #+#             */
/*   Updated: 2020/04/27 14:15:44 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_word(char *line)
{
	char	*word;
	char	*p;

	word = ft_strdup(line);
	p = word;
	if (*p == '?')
		return (word);
	while (((*p >= 'A') && (*p <= 'Z')) || ((*p >= 'a') && (*p <= 'z')) \
		|| ((*p >= '0') && (*p <= '9')) || (*p == '_'))
		p++;
	*p = 0;
	return (word);
}