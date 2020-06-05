/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:56:51 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/23 18:13:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mslerr_add(int err_number, char *err_desc)
{
	t_msl_error *new_err;

	new_err = (t_msl_error*)ft_calloc(sizeof(t_msl_error), 1);
	new_err->next = g_msl_error;
	new_err->err_number = err_number;
	new_err->err_desc = ft_strdup(err_desc);
	g_msl_error = new_err;
}

void	mslerr_deinit(void)
{
	t_msl_error *tmp;

	tmp = g_msl_error;
	while (g_msl_error)
	{
		tmp = g_msl_error;
		g_msl_error = g_msl_error->next;
		free(tmp->err_desc);
		free(tmp);
	}
	g_msl_error = NULL;
}

/*
** returns the original error message from the linked list.
** it must be duplicated using mslerr_geterr before use
*/

char	*mslerr_getmessage(int err_number)
{
	char		*s;
	t_msl_error *tmp;

	s = NULL;
	tmp = g_msl_error;
	while (tmp && !(s))
	{
		if (tmp->err_number == err_number)
			s = tmp->err_desc;
		tmp = tmp->next;
	}
	if (!s)
		s = ERROR_UNKNOWN_MSG;
	return (s);
}
