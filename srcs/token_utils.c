/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:38:57 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/03 14:47:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tkn_token_to_str(int token)
{
	char *s;

	if (token <= TK_REDIR_RIGHT)
	{
		s = ft_strdup(" ");
		s[0] = TK_MTCHARS[token - 1];
	}
	token == TK_REDIR_DBL_RIGHT ? s = ft_strdup(">>") : 0;
	token == TK_OP_DBL_AMPERSTD ? s = ft_strdup("&&") : 0;
	token == TK_OP_DBL_PIPE ? s = ft_strdup("||") : 0;
	token == TK_OP_PIPE_AMPERSTD ? s = ft_strdup("|&") : 0;
	token == TK_OP_DBL_SEMICOLON ? s = ft_strdup(";;") : 0;
	token == TK_OP_SEMICOLON_AMPERSTD ? s = ft_strdup(";&") : 0;
	token == TK_REDIR_LEFT_ERR ? s = ft_strdup("<&") : 0;
	token == TK_REDIR_RIGHT_ERR ? s = ft_strdup(">&") : 0;
	token == TK_OP_DBL_SEMIC_AMPER ? s = ft_strdup(";;&") : 0;
	token == TK_REDIR_DBL_RIGHT_ERR ? s = ft_strdup(">>&") : 0;
	token == TK_MT_NEWLINE ? s = ft_strdup("newline") : 0;
	token == TK_MT_EOF ? s = ft_strdup("eof") : 0;
	return (s);
}
