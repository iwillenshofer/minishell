/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 11:21:23 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/05 07:49:52 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_echo(struct s_command *com)
{
	size_t	i;
	int		*nonewline;
	char	*str;

	str = NULL;
	nonewline = get_arg_opt(com, "-n", ARG_UNTIL_FAIL);
	if (ft_stridentical(com->args[1], "-n"))
		i = 1;
	else
		i = 0;
	while (++i < com->argc)
	{
		str = ft_strcatxl(str, com->args[i]);
		if (i + 1 < com->argc)
			str = ft_strcatxl(str, " ");
	}
	if (!nonewline)
		str = ft_strcatxl(str, "\n");
	ft_putstr(str);
	free(str);
	free(nonewline);
	set_errno(NO_ERROR);
}

void	msh_exit(struct s_command *com)
{
	ft_putstr(EXIT_ALERT);
	if (com->argc == 1)
	{
		die(NO_ERROR);
	}
	if (ft_isnumber(com->args[1]))
	{
		if (com->argc > 2)
		{
			g_errno = ERROR_N_TOO_MANY_ARGS;
			errno = ERROR_N_TOO_MANY_ARGS;
			mslerr_print(ERROR_TOO_MANY_ARGS, ERROR_PATTERN_GRACE,
				"./minishell", NULL);
			return ;
		}
		else
			die_gracefully(NO_ERROR, ft_atoi(com->args[1]));
	}
	else
		die_gracefully(ERROR_NUMERIC_NEEDED, 2);
}

void	msh_export(struct s_command *com)
{
	int		i;
	char	*test;

	if (!com->args[1])
	{
		empty_export(com);
		return ;
	}
	i = -1;
	test = ft_strtrunc(com->args[1], '=');
	if (invalid_env_key(test))
		return ;
	test = ft_strx(get_env(test), test);
	if (test)
		msh_unset(com);
	while (g_env[++i])
		NULL;
	g_env[i] = ft_strdup(com->args[1]);
	free(test);
	set_errno(NO_ERROR);
}

void	empty_export(struct s_command *com)
{
	int		i;
	char	*untileq;
	char	*line;

	i = -1;
	while (g_env[++i])
	{
		line = ft_strdup(g_env[i]);
		untileq = ft_strtrunc(line, '=');
		ft_putstr("declare -x ");
		ft_putstr(untileq);
		ft_putstr("=\"");
		ft_putstr(line + ft_strlen(untileq) + 1);
		ft_putstr("\"");
		ft_putstr("\n");
		free(line);
		free(untileq);
	}
	(void)com;
	set_errno(NO_ERROR);
}
