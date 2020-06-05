/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:31:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/06/04 16:58:34 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# ifndef NULL
#  define NULL 0
# endif

# define GNL_LINEBREAK_RETURN 1
# define GNL_LINEBREAK_OMMIT 0

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

char			*ft_itoa(int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isprint(int c);
int				ft_lstsize(t_list *lst);
int				ft_atoi(const char *str);
t_list			*ft_lstlast(t_list *lst);
size_t			ft_strlen(const char *s);
t_list			*ft_lstnew(void *content);
char			*ft_strdup(const char *s1);
void			ft_bzero(void *s, size_t n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
t_list			*ft_lstmap(t_list *lst,
									void *(*f)(void *), void (*del)(void *));
char			*ft_strnstr(const char *haystack,
										const char *needle, size_t len);

/*
** iwillens additions:
*/

int				ft_findstr(char *str, char c);
int				ft_islower(int c);
int				ft_isspace(int c);
int				ft_isupper(int c);
void			ft_putchar(char c);
void			ft_putnbr(int nb);
void			ft_putstr(char *str);
int				ft_isblank(int c);
void			ft_putendl(char *s);

/*
** fde-capu collaborations:
*/

int				ft_stridentical(const char *s1, const char *s2);
char			*ft_strcat(const char *dst, const char *src);
char			*ft_strcatx(char *dst, char *src);
char			*ft_strcatxl(char *dst, char *src);
char			*ft_strcatxr(char *dst, char *src);
char			*ft_strtrunc(char *dst, char trunc);
char			*ft_join(char **split);
char			*ft_lastchar(char *str);
void			ft_strfree2d(char **str);
char			*ft_get_word(char *line);
char			*ft_strcatchrx(char *dst, char *c);
char			*ft_strx(char *s1, char *s2);
u_int8_t		ft_bit8_get(u_int8_t *data, u_int8_t bit);
void			ft_bit8_set(u_int8_t *data, u_int8_t bit, u_int8_t val);
void			ft_bit8_tog(u_int8_t *data, u_int8_t bit);
char			*ft_bit8_str(u_int8_t data);
int				ft_chrinset(char *r, char const *sset);
char			*ft_removequotes(char *quoted);
int				ft_isnumber(char *str);

#endif
