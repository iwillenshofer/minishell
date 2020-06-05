/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:56:19 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/05 15:18:54 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT || signal == SIGNAL_EOF)
	{
		if (signal == SIGINT)
		{
			g_errno = ERROR_CTRL_C;
			write(0, "\b\b  \b\b", 6);
		}
		ft_putstr("\n");
		ft_putstr_color(PROMPT);
		ft_putstr_color(PROMPT_END);
		free(g_stream.s);
		g_stream.s = NULL;
		g_stream.gnl = 1;
		free(g_stream.c);
		g_stream.c = NULL;
		com_free_all(g_com_head);
		g_stream.eof = 1;
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr("\e[2K");
		ft_putstr("\e[G");
		ft_putstr_color(PROMPT);
		ft_putstr_color(PROMPT_END);
	}
}

void	parent_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr("\n");
		g_flags |= FLAG_SIGINT;
	}
	if (signal == SIGQUIT)
	{
		g_flags |= FLAG_SIGQUIT;
	}
}

int		check_signal_flags(void)
{
	if (g_flags & FLAG_SIGQUIT)
	{
		g_flags ^= FLAG_SIGQUIT;
		set_errno(ERROR_SIGQUIT);
		return (1);
	}
	if (g_flags & FLAG_SIGINT)
	{
		g_flags ^= FLAG_SIGINT;
		g_errno = ERROR_CTRL_C;
		errno = ERROR_CTRL_C;
		return (0);
	}
	return (0);
}

void	hook_signals(int caller_type, int pid)
{
	if (caller_type == EXEC_ROOT)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
	else if (caller_type == EXEC_FORKED)
	{
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
		else
		{
			signal(SIGINT, parent_signal_handler);
			signal(SIGQUIT, parent_signal_handler);
		}
	}
}

/*
** this function is called by read_line and checks if the pressed key is EOF
** ignoring it if necessary or exiting the program if cursor is at pos 0.
*/

void	check_eof_signal(char *str)
{
	write(0, "  \b\b", 4);
	if (!(g_stream.s) && (!(str) || !(ft_strlen(str))))
	{
		free(str);
		ft_putstr_color("#3exit#0\n");
		die(NO_ERROR);
	}
	else if (g_stream.s && str && !(ft_strlen(str)))
		signal_handler(SIGNAL_EOF);
}
