/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:00:03 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/29 15:30:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** a simple strlen function
*/

size_t		gnl_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size] != '\0')
		size++;
	return (size);
}

char		*gnl_strdup(const char *s1)
{
	size_t	i;
	size_t	tot_bytes;
	char	*mem;

	tot_bytes = gnl_strlen(s1) + 1;
	i = 0;
	if (!(mem = (char*)malloc(tot_bytes)))
		return (NULL);
	while (i < tot_bytes)
	{
		mem[i] = s1[i];
		i++;
	}
	return (mem);
}

/*
** checks if buffer size is a valid positive number.
*/

void		gnl_shiftbuffer(char *buffer, size_t size)
{
	ssize_t i;
	ssize_t j;

	j = 0;
	while (j < (ssize_t)size)
	{
		i = 0;
		while (i < BUFFER_SIZE - 1)
		{
			buffer[i] = buffer[i + 1];
			i++;
		}
		buffer[BUFFER_SIZE - 1 - j] = '\0';
		j++;
	}
}

int			gnl_getret(t_gnl *gnl, int fd)
{
	int ret;

	ret = 0;
	if (!(ret = gnl_strlen(gnl->buffer)))
	{
		if (gnl->eof)
		{
			gnl->eof = 0;
			return (0);
		}
		ret = read(fd, gnl->buffer, BUFFER_SIZE);
		if (ret < BUFFER_SIZE && fd > 0)
			gnl->eof = 1;
		else
			gnl->eof = 0;
	}
	if (!(ret))
		return (0);
	return (ret);
}

/*
** find a linebreak on the buffer, indicating a new line.
** returns 0 if linebreak was found on the first position
** returns -1 if no linebreak was found
** returns -2 \0 was found(eof)
*/

ssize_t		gnl_find_linebreak(t_gnl *gnl, ssize_t ret)
{
	int i;

	i = 0;
	gnl->nofinalbreak = 0;
	if ((gnl->buffer[0] == '\0' && gnl->eof == 1) || ret <= 0)
		return (-2);
	while (i < ret)
	{
		if (gnl->buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	if (gnl->eof && i)
	{
		gnl->nofinalbreak = 1;
		return (i + 1);
	}
	return (-1);
}
