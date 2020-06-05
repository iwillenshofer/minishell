/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 14:45:28 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/25 18:01:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this function counts and creates each pipe
** are first, last or middle pipe.
*/

int		setup_pipes(t_com *start)
{
	t_com	*pipestart;
	int		count;

	count = 0;
	pipestart = start->op.next;
	while (pipestart && pipestart->operation == TK_OP_PIPE)
	{
		pipe(pipestart->pipes);
		count++;
		pipestart = pipestart->op.next;
	}
	return (count);
}

/*
** close parent pipes
*/

void	close_parent_pipes(t_com *com)
{
	if (com->op.previous && com->op.previous->type == TK_OP_PIPE)
	{
		close(com->op.previous->pipes[0]);
		close(com->op.previous->pipes[1]);
	}
}

/*
** closes all pipes
*/

void	close_pipes(t_com *start)
{
	t_com	*pipestart;

	pipestart = start->op.next;
	while (pipestart && pipestart->operation == TK_OP_PIPE)
	{
		close(pipestart->pipes[0]);
		close(pipestart->pipes[1]);
		pipestart = pipestart->op.next;
	}
}

void	set_parentfd(t_com *com)
{
	if (com->com.previous && com->op.previous
	&& com->op.previous->operation == TK_OP_PIPE)
	{
		close(0);
		dup2(com->op.previous->pipes[0], 0);
		close(com->op.previous->pipes[0]);
	}
	if (com->op.next->operation == TK_OP_PIPE)
	{
		close(1);
		dup2(com->op.next->pipes[1], 1);
		close(com->op.next->pipes[1]);
	}
}

void	set_childrenfd(t_com *com, t_com *start)
{
	if (com->com.previous && com->op.previous->operation == TK_OP_PIPE)
	{
		close(0);
		dup2(com->op.previous->pipes[0], 0);
	}
	if (com->op.next->operation == TK_OP_PIPE)
	{
		close(1);
		dup2(com->op.next->pipes[1], 1);
	}
	close_pipes(start);
}
