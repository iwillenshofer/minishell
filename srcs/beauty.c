/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beauty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 10:15:44 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/14 13:52:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_bgcode(char c, char **s)
{
	c == 'R' ? *s = CR : 0;
	c == 'M' ? *s = CM : 0;
	c == 'Z' ? *s = CZ : 0;
	c == 'S' ? *s = CBOLD : 0;
	c == 'G' ? *s = CG : 0;
	c == 'H' ? *s = CH : 0;
	c == 'I' ? *s = CI : 0;
	c == 'J' ? *s = CJ : 0;
	c == 'K' ? *s = CK : 0;
}

void	get_colorcode(char c, char **str)
{
	char *s;

	s = NULL;
	c == '0' ? s = C0 : 0;
	c == '1' ? s = C1 : 0;
	c == '2' ? s = C2 : 0;
	c == '3' ? s = C3 : 0;
	c == '4' ? s = C4 : 0;
	c == '5' ? s = C5 : 0;
	c == '6' ? s = C6 : 0;
	c == '7' ? s = C7 : 0;
	c == '8' ? s = C8 : 0;
	c == '9' ? s = C9 : 0;
	c == 'A' ? s = CA : 0;
	c == 'B' ? s = CB : 0;
	c == 'C' ? s = CC : 0;
	c == 'D' ? s = CD : 0;
	c == 'E' ? s = CE : 0;
	c == 'F' ? s = CF : 0;
	get_bgcode(c, &s);
	if (s)
		*str = ft_strcatxl(*str, s);
}

/*
** a 'mini printf' that parses the pattern filling it with
** error number and error message.
*/

char	*get_colors(char *str)
{
	char	*s;
	int		i;
	char	c[2];

	c[1] = '\0';
	s = ft_strdup("");
	i = 0;
	while (str[i])
	{
		c[0] = str[i];
		if (str[i] == '#')
		{
			i++;
			get_colorcode(str[i], &s);
		}
		else
			s = ft_strcatxl(s, (char*)&c);
		i++;
	}
	return (s);
}

/*
** replaces str by a new string with color codes
*/

char	*get_colorsx(char *str)
{
	char *tmp;

	tmp = str;
	if (str)
	{
		str = get_colors(str);
		free(tmp);
	}
	return (str);
}

void	ft_putstr_color(char *s)
{
	char *color;

	color = get_colors(s);
	ft_putstr(color);
	free(color);
}
