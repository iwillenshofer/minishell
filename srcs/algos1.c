/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:54:20 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/05 07:37:13 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_pwd(struct s_command *com)
{
	char	*buf;

	buf = (char *)ft_calloc(1, PATH_MAX);
	if (!getcwd(buf, PATH_MAX))
	{
		set_errno(errno);
		return ;
	}
	ft_putstr(buf);
	free(buf);
	ft_putstr("\n");
	(void)com;
	set_errno(NO_ERROR);
}

void	msh_cd(struct s_command *com)
{
	char	*home;

	home = get_env("HOME");
	if (!com->args[1])
		com_add_argument(&com, ft_strdup(home));
	if (!ft_findstr("~", *com->args[1]))
		com->args[1] = ft_strx(ft_strcat(home, \
			&com->args[1][1]), com->args[1]);
	free(home);
	set_errno(chdir(com->args[1]) >= 0 ? NO_ERROR : 1);
}

void	msh_env(struct s_command *com)
{
	int		i;
	char	*out;

	i = -1;
	out = ft_strdup("");
	while (g_env[++i])
	{
		out = ft_strcatxl(out, g_env[i]);
		if (g_env[i + 1])
			out = ft_strcatxl(out, "\n");
	}
	ft_putstr(out);
	ft_putstr("\n");
	free(out);
	(void)com;
	set_errno(NO_ERROR);
}

void	msh_unset(struct s_command *com)
{
	int		i;
	char	*name;
	int		valid;

	name = ft_strtrunc(com->args[1], '=');
	if (invalid_env_key(name))
		return ;
	valid = 0;
	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(name, g_env[i], ft_strlen(name)))
			valid = 1;
		if (valid)
		{
			free(g_env[i]);
			if (g_env[i + 1])
				g_env[i] = ft_strdup(g_env[i + 1]);
			else
				g_env[i] = 0;
		}
	}
	free(name);
	set_errno(NO_ERROR);
}

void	die_gracefully(int err_msg_num, int err_return)
{
	g_errno = err_return;
	errno = err_return;
	if (err_msg_num)
		mslerr_print(err_msg_num, ERROR_PATTERN_GRACE, "./minishell", NULL);
	minishell_free();
	exit(g_errno);
	return ;
}
