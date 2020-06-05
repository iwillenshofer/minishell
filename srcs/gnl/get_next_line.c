/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:44:34 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/29 08:51:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** reallocs (or allocate for the first time) memory for the string
** as it is being increased by the buffer's content.
*/

char	*gnl_get_line(char *str, char *buffer, size_t size)
{
	size_t	str_len;
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = str;
	str_len = gnl_strlen(tmp);
	str = (char*)malloc(sizeof(char) * (str_len + (size)));
	i = 0;
	while (tmp && tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	j = 0;
	while (j < (size - 1))
	{
		str[i + j] = buffer[j];
		j++;
	}
	gnl_shiftbuffer(buffer, size);
	str[(str_len + size) - 1] = '\0';
	if (tmp)
		free(tmp);
	return (str);
}

/*
** creates buffer and reads until end of line
** read function: ssize_t read(int fildes, void *buf, size_t nbyte);
** the return should be:
**
** 1 :  A line has been read
** 0 :  EOF has been reached
** -1 :  An error happened
*/

int		get_next_loop(int fd, char **line, t_gnl *gnl, t_var *var)
{
	int pos;

	pos = 0;
	while (line && (var->ret = gnl_getret(gnl, fd)) > 0)
	{
		pos = gnl_find_linebreak(gnl, var->ret);
		if (pos == -2)
		{
			*line = gnl_strdup("");
			gnl->eof = 0;
			return (0);
		}
		else if (pos == -1)
			var->str = gnl_get_line(var->str, gnl->buffer, var->ret + 1);
		else
		{
			var->str = gnl_get_line(var->str, gnl->buffer, pos);
			*line = var->str;
			if (gnl->eof && gnl->nofinalbreak)
				return (0);
			return (1);
		}
	}
	return (-1);
}

void	gnl_varinit(t_var *var)
{
	var->str = NULL;
	var->ret = 0;
	var->pos = 0;
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	gnl;
	t_var			var;

	gnl_varinit(&var);
	if (!(line))
		return (-1);
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		*line = NULL;
		return (-1);
	}
	var.pos = get_next_loop(fd, line, &gnl, &var);
	if (var.pos >= 0)
		return (var.pos);
	if (var.str)
		*line = var.str;
	else
		*line = gnl_strdup("");
	if (var.ret == 0)
		return (0);
	return (-1);
}
