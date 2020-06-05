/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:40:48 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/02 14:40:30 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stream	g_stream;

void	prompt_loop(int fd, char **s, char **line, int *gnl)
{
	int		psr;

	hook_signals(EXEC_ROOT, 0);
	psr = 0;
	if (fd == 0)
		ft_putstr_color(PROMPT);
	while ((!(*s) || (psr = parser(*s))) && (*gnl > 0 || (psr & PSR_EOF)))
	{
		if (fd == 0 && !(psr & PSR_EOF))
			ft_putstr_color(PROMPT_END);
		if (fd > 0)
			*gnl = get_next_line(fd, line);
		else
			*gnl = read_line(line);
		if (*gnl || fd > 0)
			*line = ft_strcatxl(*line, "\n");
		*s = *s ? *s : ft_calloc(1, 1);
		*s = ft_strcatx(*s, *line);
	}
	if (fd > 0 && *gnl == 0 && psr == 1)
		mslerr_print(ERROR_FD, NULL, NULL, NULL);
}

/*
** As we have to wait for a break signal (CTRL+C), to interrupt the signal
** and it will be listened to in main()  it may make sense to include char *s
** also in main and send it as an argument to prompt() so it can be freeid in
** case of interrupt or exit;
** an error checking must be added here, as if it returns -1,
** it is definetly a malloc error
*/

int		prompt(int fd)
{
	g_stream.gnl = 1;
	while (g_stream.gnl > 0)
	{
		g_stream.line = NULL;
		g_stream.s = NULL;
		prompt_loop(fd, &g_stream.s, &g_stream.line, &g_stream.gnl);
		if (g_com_head)
		{
			subst_envs_and_backslashes();
			subst_quotes();
			sequencer();
			exec_chain();
			com_free_all(g_com_head);
		}
		free(g_stream.s);
		g_stream.s = NULL;
	}
	return (NO_ERROR);
}
