/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequencer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:50:08 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/15 21:27:47 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** moves to next ';' or to eof
*/

t_com	*seq_movenextchain(t_com *com)
{
	while (com && (com->type != T_CMD_OPERATION
	|| (com->type == T_CMD_OPERATION
	&& (com->operation != TK_OP_SEMICOLON
	&& com->operation != TK_MT_EOF
	&& com->operation != TK_MT_NEWLINE))))
		com = com->next;
	return (com);
}

/*
** if an argument follows a redirection, its type
** is changed into 'T_CMD_FILE'.
*/

void	seq_setfiles(void)
{
	t_com *com;

	com = g_com_head;
	while (com)
	{
		if (com->type == T_CMD_OPERATION)
		{
			if (rd_is_redirect(com))
			{
				com->type = T_CMD_REDIR;
				com->next->type = T_CMD_FILE;
				com->next->operation = 0;
			}
		}
		com = com->next;
	}
	return ;
}

/*
** sets the next_com or next_op (according to com_type)
** of each t_com.
*/

void	seq_fillcom(size_t com_type)
{
	t_com	*tmp;
	t_com	*next_com;
	t_dir	*op;

	tmp = g_com_head;
	while (tmp && tmp->next)
	{
		next_com = tmp->next;
		op = &tmp->com;
		if (com_type == T_CMD_OPERATION)
			op = &tmp->op;
		op->next = NULL;
		while (next_com)
		{
			if (next_com->type == com_type)
			{
				op->next = next_com;
				break ;
			}
			next_com = next_com->next;
		}
		tmp = tmp->next;
	}
	com_type == T_CMD_OPERATION ? g_com_head_op = g_com_head->op.next : NULL;
	return ;
}

/*
** sets all files, coms and ops calling the respective functions
** then sets all the previous coms and ops for eacho t_com
*/

void	sequencer(void)
{
	t_com	*tmp;
	t_com	*prev;
	t_com	*prev_com;
	t_com	*prev_op;

	seq_setfiles();
	seq_fillcom(T_CMD_COMMAND);
	seq_fillcom(T_CMD_OPERATION);
	prev = NULL;
	prev_com = NULL;
	prev_op = NULL;
	tmp = g_com_head;
	while (tmp)
	{
		tmp->previous = prev;
		tmp->op.previous = prev_op;
		tmp->com.previous = prev_com;
		if (tmp->type == T_CMD_OPERATION)
			prev_op = tmp;
		if (tmp->type == T_CMD_COMMAND)
			prev_com = tmp;
		prev = tmp;
		tmp = tmp->next;
	}
	return ;
}
