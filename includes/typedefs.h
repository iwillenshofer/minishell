/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:44:23 by fde-capu          #+#    #+#             */
/*   Updated: 2020/05/17 11:42:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct			s_fd
{
	int					in;
	int					out;
}						t_fd;

typedef struct			s_dir
{
	struct s_command	*next;
	struct s_command	*previous;
}						t_dir;

typedef struct			s_command
{
	size_t				type;
	size_t				operation;
	char				**args;
	size_t				argc;
	char				*fullpath;
	int					pipes[2];
	int					(*func)(struct s_command *com);
	t_dir				com;
	t_dir				op;
	struct s_command	*previous;
	struct s_command	*next;
}						t_com;

typedef struct			s_functions
{
	char				*name;
	void				*function;
	int					exec;
	struct s_functions	*next;
}						t_func;

typedef struct			s_keystate
{
	int	quote;
	int	dquote;
	int escape;
	int pipe;
}						t_keystate;

typedef struct			s_chr
{
	char		chr;
	t_keystate	state;
	char		breaker;
}						t_chr;

typedef struct			s_stream
{
	char	*s;
	char	*line;
	int		gnl;
	int		eof;
	t_chr	*c;
	int		fd;
}						t_stream;

#endif
