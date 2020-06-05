/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 05:58:18 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/01 13:58:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** helper function for get_token. Treats redirections
*/

void			get_token_redir(t_chr *c, int pos, int *tk)
{
	if (*tk == TK_OP_AMPERSTD)
	{
		if (c[pos + 1].breaker == '<')
			*tk = TK_REDIR_LEFT_ERR;
		else if (c[pos + 1].breaker == '>')
		{
			*tk = TK_REDIR_RIGHT_ERR;
			if (c[pos + 2].breaker == '>')
				*tk = TK_REDIR_DBL_RIGHT_ERR;
		}
	}
	else if (*tk == TK_REDIR_RIGHT && c[pos + 1].breaker == '&')
		*tk = TK_REDIR_RIGHT_ERR;
	else if (*tk == TK_REDIR_LEFT && c[pos + 1].breaker == '&')
		*tk = TK_REDIR_LEFT_ERR;
	else if (*tk == TK_REDIR_DBL_RIGHT && c[pos + 2].breaker == '&')
		*tk = TK_REDIR_DBL_RIGHT_ERR;
}

/*
** helper function for get_token. Treats pipes and semicolons
*/

void			get_token_pipe_semic(t_chr *c, int pos, int *tk)
{
	if (*tk == TK_OP_PIPE)
	{
		if (c[pos + 1].breaker == '|')
			*tk = TK_OP_DBL_PIPE;
		else if (c[pos + 1].breaker == '&')
			*tk = TK_OP_PIPE_AMPERSTD;
	}
	else if (*tk == TK_OP_SEMICOLON)
	{
		if (c[pos + 1].breaker == ';')
			*tk = TK_OP_DBL_SEMICOLON;
		else if (c[pos + 1].breaker == '&')
			*tk = TK_OP_SEMICOLON_AMPERSTD;
	}
}

/*
** gets which token 't_chr c' stands for.
** it may take up to three t_chrs to build a token
** it returns the token directly to *tk and returns an
** int with how many chars it needed to build that token
*/

int				get_token(t_chr *c, int pos, int *tk)
{
	*tk = ft_findstr(TK_MTCHARS, c[pos].chr) + 1;
	if (*tk == TK_REDIR_RIGHT && c[pos + 1].breaker == '>')
		*tk = TK_REDIR_DBL_RIGHT;
	if (*tk == TK_OP_AMPERSTD && c[pos + 1].breaker == '&')
		*tk = TK_OP_DBL_AMPERSTD;
	if (*tk == TK_OP_PIPE || *tk == TK_OP_SEMICOLON)
		get_token_pipe_semic(c, pos, tk);
	if (*tk == TK_OP_AMPERSTD || *tk == TK_REDIR_DBL_RIGHT ||
		*tk == TK_REDIR_LEFT || *tk == TK_REDIR_RIGHT)
		get_token_redir(c, pos, tk);
	if (*tk == TK_OP_DBL_SEMICOLON && c[pos + 2].breaker == '&')
		*tk = TK_OP_DBL_SEMIC_AMPER;
	return ((*tk / 100) + 1);
}

/*
** checks if the current token is a '#', and if so, skip to the next
** line or EOF.
*/

void			tkn_checkhashtag(t_chr *c, int *i, int *token)
{
	if (*token == TK_MT_HASHTAG)
	{
		while (*token != TK_MT_NEWLINE && *token != TK_MT_EOF)
		{
			while (!(c[*i].breaker))
				(*i)++;
			*i += get_token(c, *i, token);
		}
	}
}

/*
** converts all t_chrs into commands or operations, creating an element
** in a linked list for each of them, thus completing the split innitiated
** by the parser.
*/

void			tokenize(t_chr *c, char *s, int count)
{
	int		i;
	int		start;
	int		tk;
	t_com	*command;

	i = 0;
	command = NULL;
	c[count].breaker = TK_MT_EOF;
	while (i <= count)
	{
		start = i;
		while (!(c[i].breaker))
			i++;
		if (i != start)
			com_add_argument(&command, ft_substr(s, start, i - start));
		i += get_token(c, i, &tk);
		tkn_checkhashtag(c, &i, &tk);
		if (!(tk == TK_MT_SPACE || tk == TK_MT_TAB || tk == TK_MT_NEWLINE)
			|| (i >= count - 1 && tk == TK_MT_NEWLINE))
		{
			command ? com_addback(&g_com_head, command) : 0;
			com_add_operation(tk);
			command = NULL;
		}
	}
}
