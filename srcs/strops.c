/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 09:49:11 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/04 15:39:58 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subst_quotes(void)
{
	t_com	*c;
	size_t	i;
	char	*unq;

	c = g_com_head;
	while (c)
	{
		i = 0;
		while (i < c->argc)
		{
			unq = ft_removequotes(c->args[i]);
			free(c->args[i]);
			c->args[i++] = unq;
		}
		c = c->next;
	}
	return ;
}

void	subst_envs_and_backslashes(void)
{
	t_com	*c;
	size_t	i;

	c = g_com_head;
	while (c)
	{
		i = 0;
		while (i < c->argc)
			subst_env_line(&c->args[i++]);
		c = c->next;
	}
	return ;
}

void	switch_quote(u_int8_t *quote, char *p)
{
	if (*p == '\'')
		ft_bit8_tog(quote, 1);
	if (*p == '\"')
		ft_bit8_tog(quote, 2);
	return ;
}

/*
** subst_env_line
** Conclusion by considering outputs:
** out of quotes: exec \'s
** inside of ' ': ignore \'s
** inside of " ": exec only \\'s
** quote data:
** 0b00000110
**        |\_ 1. inside single quotes
**        \__ 2. inside double quotes
*/

void	subst_env_line(char **str)
{
	char		*p;
	u_int8_t	quote;
	char		*out;

	out = ft_strdup("");
	p = *str;
	quote = 0;
	while (*p)
	{
		switch_quote(&quote, p);
		if (valid_backslash(p, quote))
			out = ft_strcatchrx(out, ++p);
		else
		{
			if ((*p == '$') && (!ft_bit8_get(&quote, 1)))
				p += subst_env_word(p, &out);
			else
				out = ft_strcatchrx(out, p);
		}
		p++;
	}
	*str = ft_strx(out, *str);
}
