/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 12:48:24 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/12 14:40:00 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** returns 0 if first type in the list is an operator instead of a command
*/

int	synx_checkfirst_op(void)
{
	t_com	*tmp;

	tmp = g_com_head;
	while (tmp && tmp->type == T_CMD_OPERATION
		&& (tmp->operation == TK_MT_SPACE && tmp->operation == TK_MT_TAB))
		tmp = tmp->next;
	if (tmp && tmp->type == T_CMD_OPERATION
		&& (tmp->operation != TK_MT_EOF && tmp->operation != TK_MT_NEWLINE))
		return (tmp->operation);
	return (0);
}

int	synx_checklast_op(t_com *t1, t_com *t2)
{
	if (t2->type == T_CMD_COMMAND)
		return (0);
	if ((t2->type == T_CMD_OPERATION
	&& (t2->operation == TK_MT_EOF || t2->operation == TK_MT_NEWLINE)))
	{
		if (t1->operation != TK_OP_SEMICOLON && t1->operation != TK_MT_NEWLINE \
			&& t1->operation != TK_OP_PIPE \
			&& t1->operation != TK_OP_DBL_AMPERSTD)
			return (t2->operation);
		else
			return (0);
	}
	else if (t2->type == T_CMD_OPERATION)
		return (t1->operation);
	return (0);
}

/*
** returns zero if two operators in a row are found.
*/

int	synx_checksyntax(void)
{
	t_com	*tmp;
	t_com	*t2;
	int		op;

	tmp = g_com_head;
	while (tmp->next)
	{
		if (tmp->type == T_CMD_OPERATION)
		{
			if ((op = synx_checkfirst_op()))
				return (op);
			t2 = tmp->next;
			while (t2)
			{
				if (!(op = synx_checklast_op(tmp, t2)))
					break ;
				else
					return (op);
				t2 = t2->next;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
