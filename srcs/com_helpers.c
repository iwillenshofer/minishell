/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 11:23:25 by fde-capu          #+#    #+#             */
/*   Updated: 2020/05/14 00:12:17 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_functiondict(void)
{
	t_func	*pointer;

	g_functions = new_com_ref("echo", msh_echo);
	pointer = g_functions;
	pointer->next = new_com_ref("pwd", msh_pwd);
	pointer = pointer->next;
	pointer->next = new_com_ref("cd", msh_cd);
	pointer = pointer->next;
	pointer->next = new_com_ref("exit", msh_exit);
	pointer = pointer->next;
	pointer->next = new_com_ref("env", msh_env);
	pointer = pointer->next;
	pointer->next = new_com_ref("export", msh_export);
	pointer = pointer->next;
	pointer->next = new_com_ref("unset", msh_unset);
	pointer = pointer->next;
	pointer->next = new_com_ref("oohwee", print_easteregg);
	return ;
}

t_func	*new_com_ref(char *name, void *function)
{
	t_func	*new;

	new = ft_calloc(1, sizeof(t_func));
	new->name = ft_strdup(name);
	new->function = function;
	return (new);
}

void	free_g_functions(t_func *f)
{
	if (f->next)
		free_g_functions(f->next);
	free(f->name);
	f->function = NULL;
	f->next = NULL;
	free(f);
	f = NULL;
	return ;
}
