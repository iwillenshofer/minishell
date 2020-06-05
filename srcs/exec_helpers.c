/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:27:07 by fde-capu          #+#    #+#             */
/*   Updated: 2020/05/13 16:26:04 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** is_known_command(*com) returns:
** and try_file(path) returns:
** -1 :: did not find file
**  0 :: successfull found executable file
**  1 :: found file but not executable
*/

int		is_known_command(struct s_command *com)
{
	char		**try[2];
	char		*trypath;
	int			found;

	if (ft_findstr(com->args[0], '/') >= 0)
	{
		com->fullpath = ft_strx(ft_strdup(com->args[0]), com->fullpath);
		return (try_file(com->args[0]));
	}
	trypath = get_env("PATH");
	try[0] = ft_split(trypath, ':');
	try[1] = try[0];
	found = -1;
	while (*try[0])
	{
		trypath = ft_strx(ft_strcat(*try[0]++, "/"), trypath);
		trypath = ft_strcatxl(trypath, com->args[0]);
		if ((found = try_file(trypath)) != -1)
			com->fullpath = ft_strx(ft_strdup(trypath), com->fullpath);
		if (found != -1)
			break ;
	}
	ft_strfree2d(try[1]);
	free(trypath);
	return (found);
}

int		try_file(char *trypath)
{
	struct stat	*statbuf;
	int			istat;
	int			is_userexect;

	statbuf = ft_calloc(sizeof(struct stat), 1);
	istat = stat(trypath, statbuf);
	is_userexect = statbuf->st_mode & S_IXUSR ? 0 : 1;
	free(statbuf);
	return (istat != -1 ? is_userexect : -1);
}

/*
** verifies if the function is builtin.
** Returns pointer to the function if found.
** otherwise returns NULL
*/

void	*is_built_in(struct s_command *com)
{
	t_func	*pointer;

	pointer = g_functions;
	while (!ft_stridentical(com->args[0], pointer->name))
	{
		if (!pointer->next)
			return (NULL);
		pointer = pointer->next;
	}
	return (com->func = pointer->function);
}

/*
** executes external functions and sets error
** appropriately
*/

void	run_proccess(struct s_command *com)
{
	execve(com->fullpath, com->args, g_env);
	minishell_exit(errno);
}
