/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:54:54 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/03 20:54:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_line(char **line)
{
	static char *str;
	char		buffer[2];
	int			ret;
	int			pos;

	if (!line)
		return (-1);
	if (!(str) && !(str = ft_calloc(1, sizeof(char))))
		return (-1);
	while (ft_findstr(str, '\n') < 0
		&& (ret = read(0, buffer, 1)) >= 0)
	{
		buffer[ret] = '\0';
		if (g_stream.eof == 1)
			str = ft_strx(ft_strdup(""), str);
		g_stream.eof = 0;
		str = ft_strcatxl(str, buffer);
		ret == 0 ? check_eof_signal(str) : 0;
	}
	pos = ft_findstr(str, '\n');
	*line = (pos >= 0) ? ft_substr(str, 0, pos)
			: ft_substr(str, 0, ft_findstr(str, '\0'));
	free(str);
	str = NULL;
	return (pos >= 0 ? 1 : 0);
}
