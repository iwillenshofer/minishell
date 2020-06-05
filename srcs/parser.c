/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:28:16 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/03 11:42:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** checks if the last operator is a '|' or '&&' and, if so, return 1
** to sign that more commands / operators are needed.
** the following comments were after return (1):
** if (com && com->operation != TK_MT_NEWLINE && com->next && (com->next->type
**			== T_CMD_OPERATION) && com->next->operation == TK_MT_EOF)
**		return (2);
*/

int		psr_checklastcommand(void)
{
	t_com *com;

	com = g_com_head;
	while (com && com->next && (com->next)->operation
		!= TK_MT_EOF && com->next->operation != TK_MT_NEWLINE)
		com = com->next;
	if (com && (com->type == T_CMD_OPERATION) && \
	(com->operation == TK_OP_PIPE || com->operation == TK_OP_DBL_AMPERSTD))
		return (1);
	return (0);
}

/*
** check if t_chrs are ready to be converted into token,
** calls tokenize if they are, returning 1 if the conversion
** ends up with missing arguments ( a trailing | or && )
** in which case it frees the linked list before requesting more
** arguments and try to tokenize again.
*/
/*
** 	if (i), WE'LL HAVE TO FREE AND CLEAR ALL THE LIST AS \
**	THE OPERATOR STILL REQUIRES MORE INFO
*/

int		psr_check_tokenready(t_keystate cur_state, t_chr *c, char *s, int i)
{
	int		last_com;
	int		err;

	last_com = 0;
	if (!(psr_getkstate(cur_state)))
	{
		tokenize(c, s, i);
		if ((err = synx_checksyntax()))
		{
			if (g_stream.fd > 0)
				die(ERROR_SYNTAX);
			set_errno(ERROR_SYNTAX);
			com_free_all(g_com_head);
			return (0);
		}
		last_com = psr_checklastcommand();
		if (last_com)
			com_free_all(g_com_head);
	}
	return (last_com);
}

/*
** allocates 2 extra spaces at the end of the line
** - to make space for a '\n'
** - to end with '\0' (automatic allocated as it is created with calloc)
*/

int		parser(char *s)
{
	t_keystate	cur_state;
	int			i;
	int			len;
	int			token_ready;

	psr_initstate(&cur_state);
	g_stream.c = (t_chr*)ft_calloc((ft_strlen(s) + 1), sizeof(t_chr));
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!(psr_getkstate(cur_state)) && ft_findstr(TK_MTCHARS, s[i]) >= 0)
			(g_stream.c)[i].breaker = s[i];
		psr_setkstate(s[i], &cur_state, &(g_stream.c)[i]);
		i++;
	}
	token_ready = psr_check_tokenready(cur_state, g_stream.c, s, i);
	free(g_stream.c);
	g_stream.c = NULL;
	return (psr_getkstate(cur_state) | token_ready);
}
