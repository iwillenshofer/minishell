/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 11:39:08 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/03 11:52:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** checks if the operator is a redirection
*/

int		rd_is_redirect(struct s_command *com)
{
	return (com->operation == TK_REDIR_LEFT
		|| com->operation == TK_REDIR_RIGHT
		|| com->operation == TK_REDIR_RIGHT_ERR
		|| com->operation == TK_REDIR_DBL_RIGHT_ERR
		|| com->operation == TK_REDIR_DBL_RIGHT
		? 1 : 0);
}

/*
** open for write and truncate file. Creates new if does not exist.
*/

int		rd_open_read(char *filename, int exec_type)
{
	int	fd;

	fd = open(filename, O_RDONLY | O_CLOEXEC);
	if (fd == -1 && exec_type == EXEC_FORKED)
	{
		minishell_free();
		exit(errno);
	}
	else if (fd == -1 && exec_type == EXEC_ROOT)
	{
		set_errno(errno);
		return (0);
	}
	close(0);
	dup2(fd, 0);
	return (1);
}

/*
** open for write and truncate file. Creates new if does not exist.
** stderr determines if fd(2) it is also redireted.
*/

int		rd_open_append(char *filename, int stderr, int exec_type)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
	if (fd == -1 && exec_type == EXEC_FORKED)
	{
		minishell_free();
		exit(errno);
	}
	else if (fd == -1 && exec_type == EXEC_ROOT)
	{
		set_errno(errno);
		return (0);
	}
	close(1);
	dup2(fd, 1);
	if (stderr == REDIR_IO_ERR)
	{
		close(2);
		dup2(fd, 2);
	}
	return (1);
}

/*
** open for write and truncate file. Creates new if does not exist.
** stderr determines if fd(2) it is also redireted.
*/

int		rd_open_write(char *filename, int stderr, int exec_type)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	if (fd == -1 && exec_type == EXEC_FORKED)
	{
		minishell_free();
		exit(errno);
	}
	else if (fd == -1 && exec_type == EXEC_ROOT)
	{
		set_errno(errno);
		return (0);
	}
	close(1);
	dup2(fd, 1);
	if (stderr == REDIR_IO_ERR)
	{
		close(2);
		dup2(fd, 2);
	}
	return (1);
}

/*
** Receives the redirection operator
** while the operator is a redirection, open the corresponding file
** for read, write or append. Each of these subfunctions will set
** the appropriate file descriptor.
** Exec_type determines wether it is being run on root or forked
*/

int		rd_set_redir(t_com *com, int exec_type)
{
	t_com	*redir;
	t_com	*file;
	int		ret;

	redir = com;
	while (rd_is_redirect(redir))
	{
		ret = 1;
		file = redir->next;
		redir->operation == TK_REDIR_RIGHT_ERR ? \
			ret = rd_open_write(file->args[0], REDIR_IO_ERR, exec_type) : 0;
		redir->operation == TK_REDIR_DBL_RIGHT_ERR ? \
			ret = rd_open_append(file->args[0], REDIR_IO_ERR, exec_type) : 0;
		redir->operation == TK_REDIR_RIGHT ? \
			ret = rd_open_write(file->args[0], REDIR_IO_NOERR, exec_type) : 0;
		redir->operation == TK_REDIR_DBL_RIGHT ? \
			ret = rd_open_append(file->args[0], REDIR_IO_NOERR, exec_type) : 0;
		redir->operation == TK_REDIR_LEFT ? \
			ret = rd_open_read(file->args[0], exec_type) : 0;
		if (!ret)
			return (0);
		redir = file->next;
	}
	return (1);
}
