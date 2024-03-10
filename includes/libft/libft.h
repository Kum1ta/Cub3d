/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:02:07 by edbernar          #+#    #+#             */
/*   Updated: 2023/12/22 13:20:40 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./File/gnl/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*ft_strnstr(const char *str, const char *to_find, size_t size);
void		*ft_memchr(const void *addr, int searchedChar, size_t size);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcat(char *dest, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		*ft_memset(void *pointer, int value, size_t count);
void		*ft_memmove(void *dest, void *src, size_t size);
void		*ft_calloc(size_t elem_count, size_t elem_size);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
char		*ft_strrchr(const char *str, int chr);
void		ft_bzero(void *pointer, size_t size);
char		*ft_strchr(const char *str, int chr);
void		free_split(char **strf, int error);
char		**ft_split(char const *s, char c);
int			ft_printf(const char *str, ...);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strdup(const char *src);
size_t		ft_strlen(const char *str);
int			ft_toupper(int character);
int			ft_tolower(int character);
t_list		*ft_lstnew(void *content);
int			ft_atoi(const char *str);
long int	ft_atol(const char *str);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
int			ft_isnumber(char *str);
char		*get_next_line(int fd);
char		*get_file(char *file);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);

#endif
