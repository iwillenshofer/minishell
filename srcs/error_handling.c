/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 12:17:06 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/05 13:45:11 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msl_error *g_msl_error;

/*
** initiate all errors.
** should we need more errors, this can be split into two or more functions
** grouping by error types. ie: mslerr_init_parsingerrors();
**
** to print an error: mslerr_print(9, 0);
**
** Those error strings would fit better at defines, but unfortunatelly,
** the Norm will not let us do that (20200604 - hope it changes someday).
*/

void	mslerr_init(void)
{
	g_msl_error = NULL;
	mslerr_add(ERROR_SYNTAX, "#ASyntax error. #MYeah. Science, huh? Ain't \
it a thing.#0");
	mslerr_add(ERROR_FD, "#AFile error. #ZThis isn't a [bleep] chocolate \
factory.#0");
	mslerr_add(ERROR_NOT_VALID_IDENTIFIER, "#AInvalid identifier. #ZI \
dropped out of school. It's not a place for smart people.#0");
	mslerr_add(ERROR_PROCESS, "#AProcess error. #ZYou do realize this will \
make the flooble crank obsolete?#0");
	mslerr_add(ERROR_PERMISSION_DENIED, "#APermission denied. #2You also \
refuse to authorize emotional countermeasures.#0");
	mslerr_add(ERROR_EXEC_FORMAT, "#AExec format error. #RHuh, it looks like \
something's wrong with the microverse battery - we're going to have to \
go inside.#0");
	mslerr_add(ERROR_NOT_FOUND, "#ANot found. #RNow let's get out of here and \
destroy this whole universe.#0");
	mslerr_add(ERROR_SYS_DUP, "#AError dup#0");
	mslerr_add(ERROR_SYS_EXEC, "#AError exec#0");
	mslerr_add(ERROR_SIGQUIT, "#AQuit. #ZAnd that guy made a universe.#0");
	mslerr_add(ERROR_TOO_MANY_ARGS, "#AToo many arguments. #ZInstead, we will \
work together to make this world a better place for all, no matter how many \
legs.#0");
	mslerr_add(ERROR_NUMERIC_NEEDED, "#ANumeric argument required. #RNothing \
you do matters! Your existence is a lie!#0");
	mslerr_add(MSG_EXIT, "#MI shouldn't be so critical. I'm an alien.#0");
}

void	mslerr_getdefaults(char **pattern, char **filename)
{
	if (!(*pattern) || !(ft_strncmp((*pattern), "", 1)))
		*pattern = ERROR_DEFAULT_PATTERN;
	if (!(*filename) || !(ft_strncmp((*pattern), "", 1)))
		*filename = ERROR_DEFAULT_FILENAME;
	else if (*pattern == ERROR_DEFAULT_PATTERN)
		*pattern = ERROR_DEFAULT_FPATTERN;
}

void	mslerr_getitems(char c, char **s, int err_number, char *filename)
{
	if (c == 'i')
		*s = ft_strcatx(*s, ft_itoa(err_number));
	else if (c == 's')
		*s = ft_strcatxl(*s, mslerr_getmessage(err_number));
	else if (c == 'f')
		*s = ft_strcatxl(*s, filename);
}

/*
** a 'mini printf' that parses the pattern filling it with
** error number and error message.
*/

char	*mslerr_geterr(int err_number, char *pattern,
							char *filename, char *argument)
{
	char	*s;
	int		i;
	char	c[2];

	c[1] = '\0';
	mslerr_getdefaults(&pattern, &filename);
	s = ft_strdup("");
	i = 0;
	while (pattern[i])
	{
		c[0] = pattern[i];
		if (pattern[i] == '%')
		{
			i++;
			mslerr_getitems(pattern[i], &s, err_number, filename);
		}
		else if (pattern[i] == '@' && argument)
			s = ft_strcatxl(s, argument);
		else
			s = ft_strcatxl(s, (char*)&c);
		i++;
	}
	free(argument);
	return (get_colorsx(s));
}

/*
** prints an error message with the appropriate pattern.
** %s for error string, %i for error number.
** patterns allowed are NULL or "" for default
** %i display error
** %s display message
** pattern example: "Error: %i, Message: %s"
** :: show_errno(err_number); :: debug.c way of testing.
*/

void	mslerr_print(int err_number, char *pattern,
							char *filename, char *argument)
{
	char *s;

	s = mslerr_geterr(err_number, pattern, filename, argument);
	ft_putstr_fd(s, STDERR_FILENO);
	free(s);
}
