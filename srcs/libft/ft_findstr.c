/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:29:19 by iwillens          #+#    #+#             */
/*   Updated: 2020/04/17 14:29:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** returns the position of a string if found
**  or -1 if not found
*/

int		ft_findstr(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}
