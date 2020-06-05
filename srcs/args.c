/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 11:33:55 by fde-capu          #+#    #+#             */
/*   Updated: 2020/04/30 08:54:19 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Behavior of ARG_UTIL_FAIL is not exactly as expected. It should further test
** something like `command->valid_options` before failing.
**
** Behavior ARG_GET_NEXT is still untested and leak prone.
*/

void	*arg_alloc(char *type, char *val)
{
	void	*ret;
	int		tmp;

	if (ft_stridentical(type, "int"))
	{
		ret = (int *)ft_calloc(sizeof(int), 1);
		tmp = ft_atoi(val);
		ft_memcpy(ret, &tmp, sizeof(int));
	}
	if (ft_stridentical(type, "char"))
	{
		ret = ft_calloc(sizeof(char) * ft_strlen(val) + 1, 1);
		ft_strlcpy(ret, val, ft_strlen(val));
	}
	return (ret);
}

void	*get_arg_opt(struct s_command *c, char *opt, int behavior)
{
	size_t	i;

	i = 0;
	while (++i < c->argc)
	{
		if (ft_stridentical(c->args[i], opt))
		{
			if (behavior & ARG_GET_NEXT)
			{
				if (i + 1 < c->argc)
					return (arg_alloc("char", c->args[i + 1]));
				else
					return (NULL);
			}
			else
				return (arg_alloc("int", "1"));
		}
		else
		{
			if (behavior & ARG_UNTIL_FAIL)
				return (NULL);
		}
	}
	return (NULL);
}
