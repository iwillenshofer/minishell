/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:39:39 by fde-capu          #+#    #+#             */
/*   Updated: 2020/05/13 09:27:00 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_free_single(t_com *com)
{
	size_t	i;

	i = -1;
	while (++i < com->argc)
		free((com->args[i]));
	free(com->args);
	free(com->fullpath);
	com->next = NULL;
	free(com);
	com = NULL;
	return ;
}

void	com_free_all(t_com *com_head)
{
	if ((com_head) && (com_head->next))
		com_free_all(com_head->next);
	if (com_head)
		com_free_single(com_head);
	g_com_head = NULL;
	return ;
}

t_com	*init_com(void)
{
	t_com	*com;

	com = ft_calloc(sizeof(t_com), 1);
	com->args = (char **)ft_calloc(1, sizeof(char *));
	com->args[0] = NULL;
	return (com);
}

void	com_addback(t_com **head, t_com *item)
{
	t_com *tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
	}
}
