/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:29:17 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/03 20:28:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** executes internal functions in parent process.
** sets the appropriate fds and returns to the original after
** function is executed.
*/

t_com	*exec_built_in(struct s_command *com)
{
	t_fd	fd;

	fd_save(&fd);
	set_parentfd(com);
	if (!rd_set_redir(com->next, EXEC_ROOT))
		return (0);
	set_errno(NO_ERROR);
	com->func(com);
	fd_restore(&fd);
	return (com);
}

/*
** executes external function on a child process.
*/

void	exec_external(t_com *com, t_com *start)
{
	int	sys;

	set_childrenfd(com, start);
	if (!(rd_set_redir(com->next, EXEC_FORKED)))
		return ;
	sys = is_known_command(com);
	if (sys == 0)
		run_proccess(com);
	else if (sys == 1)
		minishell_exit(ERROR_PERMISSION_DENIED);
	else if (sys == -1)
		minishell_exit(ERROR_NOT_FOUND);
}

/*
** forks and returns parent (exec_external must kill the child)
*/

t_com	*exec_fork(t_com *com, t_com *start)
{
	int pid;
	int status;

	pid = fork();
	hook_signals(EXEC_FORKED, pid);
	if (pid == 0)
		exec_external(com, start);
	else
	{
		close_parent_pipes(com);
		waitpid(pid, &status, 0);
		if (set_errno(WEXITSTATUS(status)))
			return (0);
		if (g_flags & FLAG_SIGQUIT)
		{
			g_flags ^= FLAG_SIGQUIT;
			set_errno(ERROR_SIGQUIT);
			return (0);
		}
	}
	return (com);
}

/*
** this function executes a chain of pipes
** or a standalone function, returning the last
** t_com it executed.
*/

t_com	*exec_pipes(t_com *com)
{
	t_com	*start;
	int		pipecount;

	start = com;
	pipecount = setup_pipes(start) + 1;
	while (pipecount && com)
	{
		if (is_built_in(com))
			com = exec_built_in(com);
		else
			com = exec_fork(com, start);
		if (!com)
			break ;
		if (com && com->com.next && pipecount > 1)
			com = com->com.next;
		pipecount--;
	}
	close_pipes(start);
	return (com);
}

/*
** executes chain of command;
*/

void	exec_chain(void)
{
	t_com	*com;
	t_com	*ret;
	t_fd	fd;

	com = g_com_head;
	if (com && com->type != T_CMD_COMMAND)
		com = com->com.next;
	while (com)
	{
		fd_save(&fd);
		if (!(ret = exec_pipes(com)))
			com = seq_movenextchain(com);
		else
			com = ret;
		fd_restore(&fd);
		com = com->com.next;
	}
}
