/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 05:59:43 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/22 06:26:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** adds an argument (argv) to an existing command
**  and creates a command (com) if it does not exist yet.
*/

void		com_add_argument(t_com **com, char *str)
{
	size_t	argc;
	char	**tmp;
	size_t	i;

	i = 0;
	argc = 0;
	if (!(*com))
		*com = init_com();
	while ((*com)->args[argc])
		argc++;
	tmp = (char**)ft_calloc(argc + 2, sizeof(char*));
	while (i < argc)
	{
		tmp[i] = (*com)->args[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	free((*com)->args);
	(*com)->args = tmp;
	(*com)->argc = argc + 1;
}

/*
** adds an operator to the command lists, separating
** each command.
*/

void		com_add_operation(size_t op_type)
{
	t_com *command;

	command = init_com();
	command->operation = op_type;
	command->type = T_CMD_OPERATION;
	com_addback(&g_com_head, command);
}
