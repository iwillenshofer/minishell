/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:54:29 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/03 19:47:47 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_init(char **envp)
{
	g_flags = 0;
	set_errno(NO_ERROR);
	init_env(envp);
	init_functiondict();
	mslerr_init();
	ft_putstr_color(LOGO0);
	ft_putstr_color(LOGO1);
	ft_putstr_color(LOGO2);
	ft_putstr_color(LOGO3);
	ft_putstr_color(LOGO4);
	ft_putstr_color(LOGO5);
	ft_putstr_color(LOGO6);
}

void	minishell_free(void)
{
	free(g_stream.s);
	free_g_functions(g_functions);
	com_free_all(g_com_head);
	mslerr_deinit();
	ft_strfree2d(g_env);
	return ;
}

void	minishell_exit(int ex_code)
{
	minishell_free();
	exit(ex_code);
}

/*
** To track *apple[] in case of incompatibility:
** //int		main(int argc, char *argv[], char *envp[], char *apple[])
** //(void)apple;
** // we will have to check the file first
*/

int		main(int argc, char *argv[], char *envp[])
{
	g_stream.fd = 0;
	minishell_init(envp);
	if (argc >= 2)
	{
		g_stream.fd = open(argv[1], O_RDONLY);
		if (g_stream.fd == -1)
			die(errno);
		else
			prompt(g_stream.fd);
	}
	while (g_errno >= 0 && g_stream.fd == 0)
		prompt(0);
	die(g_errno);
	return (g_errno);
}

void	die(int error)
{
	set_errno(error);
	minishell_free();
	exit(g_errno);
	return ;
}
