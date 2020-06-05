/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 21:31:08 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/25 18:00:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_save(t_fd *fd)
{
	(*fd).in = dup(STDIN_FILENO);
	(*fd).out = dup(STDOUT_FILENO);
}

void	fd_restore(t_fd *fd)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup2((*fd).in, STDIN_FILENO) == -1)
		die(errno);
	if (dup2((*fd).out, STDOUT_FILENO) == -1)
		die(errno);
	if (close((*fd).in) == -1)
		die(errno);
	if (close((*fd).out) == -1)
		die(errno);
}
