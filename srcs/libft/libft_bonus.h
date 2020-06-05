/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:26:47 by iwillens          #+#    #+#             */
/*   Updated: 2020/01/27 01:20:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <limits.h>

# ifndef NULL
#  define NULL 0
# endif

int		ft_islower(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
int		ft_isblank(int c);
void	ft_putendl(char *s);

#endif
