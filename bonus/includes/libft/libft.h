/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:02:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 17:28:09 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include "./File/gnl/get_next_line.h"

# define FT_HEXA_BASE "0123456789abcdef"
# define FT_HEXA_BASE_MAJ "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void		ft_lstremoveif(t_list **lst, void *e, void (*del)(), int (*cmp)());
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*ft_strnstr(const char *str, const char *to_find, size_t size);
void		*ft_memchr(const void *addr, int searchedChar, size_t size);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcat(char *dest, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_ultoa_base(unsigned long nb, const char *base);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		*ft_memset(void *pointer, int value, size_t count);
ssize_t		ft_putxnbr_fd(unsigned int nb, short maj, int fd);
char		*ft_str_insert(char *src, char *str, size_t pos);
void		*ft_memmove(void *dest, void *src, size_t size);
void		*ft_calloc(size_t elem_count, size_t elem_size);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_dprintf(int fd, const char *str, ...);
void		ft_putchar_rep(char c, int rep, int fd);
ssize_t		ft_putunbr_fd(unsigned int nb, int fd);
char		**ft_split2(char const *s, char *skip);
char		*ft_strrchr(const char *str, int chr);
void		ft_bzero(void *pointer, size_t size);
char		*ft_strchr(const char *str, int chr);
void		free_split(char **strf, int error);
char		**ft_split(char const *s, char c);
char		*ft_strfjoin(char *s1, char *s2);
ssize_t		ft_putptr_fd(void *ptr, int fd);
int			ft_printf(const char *str, ...);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strcmp(char *s1, char *s2);
ssize_t		ft_putstr_fd(char *s, int fd);
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
int			ft_isspace(char c);
float		ft_atof(char *str);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
uint32_t	ft_abs(int value);
char		*ft_itoa(int n);

#endif
