/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 11:16:29 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/03 20:24:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp)
{
	int	i;

	g_env = (char **)ft_calloc(PATH_MAX, 1);
	i = -1;
	while (envp[++i])
		g_env[i] = ft_strdup(envp[i]);
	return ;
}

char	*get_env(char *name)
{
	int		i;

	if (!ft_strlen(name))
		return (ft_strdup("$"));
	if (ft_stridentical(name, "?"))
		return (ft_itoa(g_errno));
	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(name, g_env[i], ft_strlen(name)))
			return (ft_strdup((\
				ft_strnstr(g_env[i], "=", ft_strlen(g_env[i])) + 1)));
	}
	return (ft_strdup(""));
}

int		is_valid_envkey(char *env)
{
	int	i;

	if (!ft_isalpha(*env) && (*env != '_') && (*env != '?'))
		return (0);
	if (*env == '?')
		return (1);
	i = 0;
	while (*(env + ++i))
	{
		if (!ft_isalpha(*(env + i)) && !ft_isdigit(*(env + i)) \
			&& !(*(env + i) == '_'))
		{
			return (0);
		}
	}
	return (1);
}

int		invalid_env_key(char *key)
{
	if (!is_valid_envkey(key))
	{
		free(key);
		set_errno(ERROR_NOT_VALID_IDENTIFIER);
		return (1);
	}
	return (0);
}

int		set_errno(int err)
{
	g_errno = err;
	errno = err;
	if (err == ERROR_SIGQUIT)
		mslerr_print(err, "%s\n", NULL, NULL);
	else if (err)
		mslerr_print(err, NULL, "./minishell", NULL);
	return (err);
}
