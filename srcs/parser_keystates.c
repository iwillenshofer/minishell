/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_keystates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 06:38:10 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/22 18:08:38 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** innitiates t_keystate struct
*/

void	psr_initstate(t_keystate *kstate)
{
	kstate->quote = 0;
	kstate->dquote = 0;
	kstate->pipe = 0;
	kstate->escape = 0;
}

/*
** returns if each of the argument of keystate is turned on.
**  this simple function could be done directly on the parser, but
**  was separated to allow further expansion of the program, allowing
**  more checks to be done at once.
*/

int		psr_getkstate(t_keystate kstate)
{
	return (kstate.dquote | kstate.quote | kstate.escape);
}

/*
** sets each of our key states depending on the other keystates.
** this function is used to check if we are in open quotes, which
** would bypass any commands or operations, interpreting them as strings.
*/

void	psr_setkstate(char c, t_keystate *cur_state, t_chr *key)
{
	key->chr = c;
	if (c == '\"' && !(cur_state->quote | cur_state->escape))
		cur_state->dquote = cur_state->dquote ^ 1;
	if (c == '\'' && !(cur_state->dquote | cur_state->escape))
		cur_state->quote = cur_state->quote ^ 1;
	if (c == '\\' && !(cur_state->quote | cur_state->escape))
		cur_state->escape = 1;
	else
		cur_state->escape = 0;
	key->state = *cur_state;
}
