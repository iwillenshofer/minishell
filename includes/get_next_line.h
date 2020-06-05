/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:44:49 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/28 12:39:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct	s_gnl
{
	char	buffer[BUFFER_SIZE];
	int		eof;
	int		nofinalbreak;
}				t_gnl;

typedef struct	s_var
{
	int		ret;
	ssize_t pos;
	char	*str;
}				t_var;

int				get_next_line(int fd, char **line);
size_t			gnl_strlen(const char *str);
char			*gnl_strdup(const char *s1);
void			gnl_shiftbuffer(char *buffer, size_t size);
int				gnl_getret(t_gnl *gnl, int fd);
ssize_t			gnl_find_linebreak(t_gnl *gnl, ssize_t ret);
char			*gnl_get_line(char *str, char *buffer, size_t size);
int				get_next_loop(int fd, char **line, t_gnl *gnl, t_var *var);
void			gnl_varinit(t_var *var);
int				get_next_line(int fd, char **line);

#endif
