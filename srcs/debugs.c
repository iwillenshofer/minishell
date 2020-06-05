/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 16:59:51 by fde-capu          #+#    #+#             */
/*   Updated: 2020/05/14 15:25:54 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_show(t_com *com)
{
	ft_putstr("\nnext_com:");
	ft_putnbr((int)com->com.next);
	ft_putstr("\nnext_op:");
	ft_putnbr((int)com->op.next);
	ft_putstr("\nprev_com:");
	ft_putnbr((int)com->com.previous);
	ft_putstr("\nprev_op:");
	ft_putnbr((int)com->op.previous);
	ft_putstr("\n------------\n");
	return ;
}

void	command_show(t_com *com)
{
	char	*argc;
	size_t	i;

	ft_putstr("command\nargs: ");
	i = -1;
	while (++i < com->argc)
	{
		ft_putstr(com->args[i]);
		ft_putstr("; ");
	}
	ft_putstr("\nargc: ");
	argc = ft_itoa(com->argc);
	ft_putstr(argc);
	free(argc);
	return ;
}

void	com_show(t_com *com)
{
	ft_putstr("addr: ");
	ft_putnbr((int)com);
	ft_putstr("\ntype: ");
	if (com->type == T_CMD_FILE)
	{
		ft_putstr("file\nname: ");
		ft_putstr(com->args[0]);
	}
	else if (com->type)
	{
		ft_putstr("operator\nop_type: ");
		ft_putstr(tkn_token_to_str(com->operation));
		ft_putstr("\nnext: ");
		ft_putnbr((int)com->next);
		ft_putstr("\nprevious: ");
		ft_putnbr((int)com->previous);
	}
	else
		command_show(com);
	next_show(com);
	return ;
}

void	comlist_print(void)
{
	t_com	*p;

	ft_putstr("head_com: ");
	ft_putnbr((int)g_com_head);
	ft_putstr("\nhead_op: ");
	ft_putnbr((int)g_com_head_op);
	ft_putstr("\nCommand list");
	ft_putstr("\n------------\n");
	p = g_com_head;
	while (p)
	{
		com_show(p);
		p = p->next;
	}
	return ;
}
