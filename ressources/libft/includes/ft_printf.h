/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 20:37:59 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 20:59:26 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <wchar.h>
# include <stdlib.h>
# include <stddef.h>
# include <inttypes.h>
# include <locale.h>

# include <stdio.h>

typedef struct	s_string_list
{
	void					*content;
	int						content_size;
	size_t					is_malloc : 1;
	struct s_string_list	*next;
}				t_string;

void			ft_error(int er);
int				ft_printf(const char *format, ...);
char			*ft_find_data_type(uint64_t *flags, char *str);
t_string		*ft_newlist(void *content, int size, size_t is_malloc);

/*
** tools
*/

char			*ft_process_wcharstring(char *ans, wchar_t *val);
char			*ft_process_width2(char *ans, char *c, int width);
char			*ft_process_prec2(char *ans, int i, uint64_t flags);
char			*ft_wcharstr(wchar_t c);
size_t			ft_wcharlen(const wchar_t c);
size_t			ft_calc_size(size_t strsize, uint64_t flags, int fla);
int				is_type(char c);
int				is_size(char c);
int				is_flag(char c, uint64_t flags);
int				is_parse(char c);
void			biggest(uint64_t *flags);
void			ft_process_plus(char *ans, char *str, uint64_t flags,\
				int width);
void			ft_process_shit(char *ans, uint64_t flags, int width, int zero);

/*
** process val to string
*/

t_string		*p_infos(va_list ap, const uint64_t flags);
t_string		*p_char(wchar_t val, const uint64_t flags);
char			*p_string(char *val, uint64_t flags,\
														char *c, int width);
t_string		*p_int2str(void *val, const uint64_t flags);
char			*p_int(char *str, uint64_t flags, size_t prec,\
								int width);
t_string		*p_pointer(wchar_t *val, uint64_t flags);

/*
** COLORS
*/

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

#endif
