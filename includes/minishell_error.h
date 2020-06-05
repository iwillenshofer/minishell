/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 12:17:41 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/05 13:41:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# define NO_ERROR					0
# define EXIT_SIGNAL				232
# define MSG_EXIT					1000
# define ERROR_NOT_VALID_IDENTIFIER	1
# define ERROR_NOT_FOUND			2
# define ERROR_FD					20
# define ERROR_PROCESS				3
# define ERROR_EXEC_FORMAT			8
# define ERROR_PERMISSION_DENIED	126
# define ERROR_SYNTAX				127
# define ERROR_NUMERIC_NEEDED		250
# define ERROR_TOO_MANY_ARGS		251
# define ERROR_N_TOO_MANY_ARGS		1
# define ERROR_SYS_DUP				333
# define ERROR_SYS_EXEC				334
# define ERROR_SIGQUIT				131
# define DID_NOT_DIE_PROPERLY		-3

# define ERROR_UNKNOWN_MSG "#Eerror #8Eek barba dirkle!#0\n"
# define ERROR_DEFAULT_FILENAME "./minishell"
# define ERROR_DEFAULT_PATTERN "#A%i: %s#0\n"
# define ERROR_DEFAULT_FPATTERN "#4[%f] #A%i: #A%s#0\n"
# define ERROR_PATTERN_SYNTAX_TK "#4[%f] #A%i:#8 error near: `@`. #A %s#0\n"
# define ERROR_PATTERN_GRACE "#4[%f] #A%s#0\n"
# define EXIT_ALERT "exit\n"

typedef struct		s_msl_error
{
	int					err_number;
	char				*err_desc;
	struct s_msl_error	*next;
}					t_msl_error;

extern t_msl_error	*g_msl_error;

/*
** error_handling_list
*/

char				*mslerr_getmessage(int err_number);
void				mslerr_deinit(void);
void				mslerr_add(int err_number, char *err_desc);
void				mslerr_init(void);

/*
** error_handling main functions
** patterns allowed are NULL or "" for default
** %i display error
** %s display message
** pattern example: "Error: %i, Message: %s"
** the argument is set on place of an @ in the pattern.
** the argument (as opposed to filename) is Always Freed!
** use ft_strdup if you do not wish it to be freed.
*/

char				*mslerr_geterr(int err_number, char *pattern, \
						char *filename, char *argument);
void				mslerr_print(int err_number, char *pattern, \
						char *filename, char *argument);

#endif
