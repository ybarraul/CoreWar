/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:32:46 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/03 21:25:29 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "wchar.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdbool.h>

/*
** string.h : size_t
** unistd.h : write
** stdlib.h : ?
*/

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
** string
*/

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_wstrlen(wchar_t *val);
size_t			ft_wcharlen(const wchar_t c);
char			*ft_strndup(const char *s, size_t len);
char			*ft_strmod(char *src, const char *sw, const char *del,\
				char delim);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,\
				size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrev(const char *s);
char			*ft_itoa(int n);
char			*ft_strdup(const char *src);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strmap(char const *s, char(*f)(char));
char			*ft_strmapi(char const *s, char(*f) (unsigned int, char));
char			*ft_strncpy(char *dest, const char *src, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			**ft_strsplit(char const *s, char c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnew(size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_itoa_base(intmax_t value, int base);
char			*ft_uitoa_base(uintmax_t value, int base);
char			*ft_strjoin_free(char *s1, char *str_free);
void			ft_striteri(char *s, void(*f)(unsigned int, char *));
void			ft_striter(char *s, void (*f)(char *));
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_str_tolower(char *str);
char			*ft_strnjoin_free(char *s1, char *s2, size_t n);
char			**copy_tab(char **tab);
bool			check_ifdigit(char *to_check);
bool			check_ifalphanum(char *to_check);

/*
** Tool
*/

void			ft_bzero(void *s, size_t n);
void			*ft_realloc(void *var, size_t last, size_t size);
void			ft_swap(void *a, void *b, size_t size);
void			free_tab(void **tab);
bool			match(char *s1, char*s2);

/*
** Affichage
*/

void			ft_putstr(char const *s);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(wchar_t c);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putnstr_fd(const char *str, size_t len, int fd);
void			ft_putnstr(const char *str, size_t len);

/*
** char
*/

int				ft_toupper(int c);
int				ft_tolower(int c);

/*
** list
*/

t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lsiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstdel_content(void *content, size_t content_size);
/*
** is_x
*/

int				ft_isspace(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isdigit(int c);

/*
** mem
*/

int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_memdel(void **ap);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memccpy(void *dst, void const *src, int c, size_t n);

#endif
