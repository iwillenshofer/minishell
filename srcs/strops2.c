/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strops2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:37:59 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/03 11:10:36 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** valid_backslash
** no quotes: all works \ and $ (except \n that is ignored?)
** '' quotes: all literal
** "" quotes: intepret "$'\"\\"
*/

int	valid_backslash(char *p, u_int8_t quote)
{
	return (((*p == '\\')
			&& ((!quote)
				|| (ft_bit8_get(&quote, 2)
					&& ft_chrinset(p + 1, "$'\"\\"))))
		? 1 : 0);
}

int	subst_env_word(char *p, char **out)
{
	int		word_size;
	char	*word;

	word_size = 0;
	word = ft_get_word(p + 1 + (*(p + 1) == '{' ? 1 : 0));
	*out = ft_strcatx(*out, get_env(word));
	word_size = ft_strlen(word) + (*(p + 1) == '{' ? 2 : 0);
	free(word);
	return (word_size);
}
