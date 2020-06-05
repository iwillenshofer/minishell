/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:38:02 by fde-capu          #+#    #+#             */
/*   Updated: 2020/06/05 15:15:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "typedefs.h"
# include "get_next_line.h"
# include "minishell_error.h"
# include <sys/signal.h>

/*
** CONFIG OPTIONS
*/

# define PIPE_BUFFER_SIZE 40960

extern t_stream	g_stream;

/*
** Genereral purpose aliases
** SIGNAL_EOF is a phony signal for CTRL^D
*/

# define MSH_IN 0
# define SIGNAL_EOF 999

/*
** prompt welcome ascii art and text
*/

# define LOGO0 "\n\n"
# define LOGO1 "#A"
# define LOGO2 " ___._ _. _|_  _ ||\n"
# define LOGO3 " |||||\\|||_| ||_|||\n"
# define LOGO4 " | ||| ||_|| ||_ ||\n"
# define LOGO5 "#2 Peace Among Worlds #0\n"
# define LOGO6 "#3 4 2 S P  S q u a d #0\n\n"
# define PROMPT "#5t(-_-t) #0"
# define PROMPT_END "#3:#0 "

/*
** fore-Colors, Backgrounds and decorations
*/

# define C0 "\e[0m"
# define C1 "\e[30m"
# define C2 "\e[31m"
# define C3 "\e[32m"
# define C4 "\e[33m"
# define C5 "\e[34m"
# define C6 "\e[35m"
# define C7 "\e[36m"
# define C8 "\e[37m"
# define C9 "\e[90m"
# define CA "\e[91m"
# define CB "\e[94m"
# define CC "\e[92m"
# define CD "\e[93m"
# define CE "\e[94m"
# define CF "\e[95m"
# define CR "\e[96m"
# define CM "\e[94m"
# define CZ "\e[92m"
# define CBOLD "\e[96m"
# define CG "\e[40m"
# define CH "\e[107m"
# define CI "\e[106m"
# define CJ "\e[103m"
# define CK "\e[102m"

/*
** Command types
*/

# define T_CMD_COMMAND 0
# define T_CMD_OPERATION 1
# define T_CMD_FILE 2
# define T_CMD_REDIR 3

/*
** Operators for the parser
*/

# define PSR_OK						0
# define PSR_OPENPIPE				1
# define PSR_EOF					2

/*
** signals, whether they are the root of the shell
** or forked (in which case both parent's and children's)
** signals are changed
*/

# define EXEC_ROOT 0
# define EXEC_FORKED 1

/*
** tokens (dividing by 100 + 1 determines the number of
** digits used by the token.
*/

# define TK_MTCHARS				"|&;()<>\t \n#"
# define TK_OP_PIPE					1
# define TK_OP_AMPERSTD				2
# define TK_OP_SEMICOLON			3
# define TK_OP_PAREN_O				4
# define TK_OP_PAREN_C				5
# define TK_REDIR_LEFT				6
# define TK_REDIR_RIGHT				7
# define TK_MT_TAB					8
# define TK_MT_SPACE				9
# define TK_MT_NEWLINE				10
# define TK_MT_HASHTAG				11
# define TK_MT_EOF					12
# define TK_REDIR_DBL_RIGHT			100
# define TK_OP_DBL_AMPERSTD			101
# define TK_OP_DBL_PIPE				102
# define TK_OP_PIPE_AMPERSTD		103
# define TK_OP_DBL_SEMICOLON		104
# define TK_OP_SEMICOLON_AMPERSTD   105
# define TK_REDIR_LEFT_ERR			110
# define TK_REDIR_RIGHT_ERR			111
# define TK_OP_DBL_SEMIC_AMPER		200
# define TK_REDIR_DBL_RIGHT_ERR		201

# define ARG_GET_NEXT	1
# define ARG_UNTIL_FAIL	2
# define REDIR_IO_NOERR 0
# define REDIR_IO_ERR 1

# define FLAG_SIGQUIT 1
# define FLAG_SIGINT 2

/*
** Main functions.
*/

void	minishell_free(void);
void	minishell_exit(int ex_code);

/*
** algos1 and algos2 :: builtin commands
*/

void	msh_echo(struct s_command *com);
void	msh_pwd(struct s_command *com);
void	msh_cd(struct s_command *com);
void	msh_exit(struct s_command *com);
void	msh_env(struct s_command *com);
void	msh_export(struct s_command *com);
void	msh_unset(struct s_command *com);
void	empty_export(struct s_command *com);

/*
** command helpers (listfunctions)
*/

t_func	*g_functions;
void	init_functiondict(void);
void	free_g_functions(t_func *f);
t_func	*new_com_ref(char *name, void *function);

/*
** command related globals and functions
*/

t_com	*g_com_head;
t_com	*g_com_head_op;
t_com	*init_com(void);
void	com_free_all(t_com *com_head);
void	com_free_single(t_com *com);
void	com_addback(t_com **head, t_com *item);
void	com_add_argument(t_com **com, char *str);
void	com_add_operation(size_t op_type);
void	*arg_alloc(char *type, char *val);
void	*get_arg_opt(struct s_command *c, char *opt, int behavior);

/*
** executors
*/

int		exec(t_com *com);
void	exec_chain(void);
int		try_file(char *trypath);
void	run_proccess(struct s_command *com);
t_com	*seq_movenextchain(t_com *com);
int		is_known_command(struct s_command *com);
t_com	*exec_built_in(struct s_command *com);
void	exec_external(t_com *com, t_com *start);
void	*is_built_in(struct s_command *com);

/*
** prompt
*/

int		prompt(int fd);
int		prompt_readfile(int fd);
void	prompt_loop(int fd, char **s, char **line, int *gnl);
int		read_line(char **line);

/*
** parser
*/

int		parser(char *s);
void	psr_initstate(t_keystate *kstate);
int		psr_getkstate(t_keystate kstate);
void	psr_setkstate(char c, t_keystate *cur_state, t_chr *key);
void	sequencer(void);
int		rd_is_redirect(struct s_command *com);
int		rd_set_redir(t_com *com, int exec_type);

/*
** tokenizer
*/

void	tokenize(t_chr *c, char *s, int count);
char	*tkn_token_to_str(int token);

/*
** env :: **g_env is a handmade **environ
*/

char	g_flags;
char	**g_env;
int		g_errno;
void	init_env(char **envp);
char	*get_env(char *name);
int		is_valid_envkey(char *env);
int		invalid_env_key(char *key);

/*
** Error routes
*/

int		set_errno(int err);
void	die(int error);
void	die_gracefully(int err_msg_num, int err_return);

/*
** syntax functions
*/

int		synx_checksyntax(void);

/*
** debugs
*/

void	show_errno(void);
void	com_show(t_com *com);
void	comlist_print(void);
void	next_show(t_com *com);
void	command_show(t_com *com);

/*
** string operands and beauty
*/

void	subst_quotes(void);
void	subst_envs_and_backslashes(void);
void	switch_quote(u_int8_t *quote, char *p);
void	subst_env_line(char **str);
char	*ft_strtrunc(char *dst, char trunc);
void	ft_putstr_color(char *s);
char	*get_colorsx(char *str);
char	*get_colors(char *str);
void	print_easteregg(void);
int		valid_backslash(char *p, u_int8_t quote);
int		subst_env_word(char *p, char **out);

/*
** signal handling
*/

void	signal_handler(int signal);
void	hook_signals(int caller_type, int pid);
void	check_eof_signal(char *str);
int		check_signal_flags(void);

/*
** sequencer / pipes
*/

void	set_childrenfd(t_com *com, t_com *start);
void	set_parentfd(t_com *com);
void	close_pipes(t_com *start);
void	close_parent_pipes(t_com *com);
int		setup_pipes(t_com *start);

/*
** file descriptors
*/

void	fd_save(t_fd *fd);
void	fd_restore(t_fd *fd);

#endif
