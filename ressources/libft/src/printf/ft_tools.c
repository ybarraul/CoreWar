/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/10 19:06:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/22 07:21:03 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Function : ft_calc_size
** ---------------------------
** @param strsize : size of basic string, exemple : strlen atoi
** @param flags	: every flags parsed
** @param type : 0xfff & flags only for the types which can be used
** @return the size of the total string with width, precision and other flags
*/

size_t			ft_calc_size(size_t strsize, uint64_t flags, int type)
{
	size_t		s;
	size_t		width;
	size_t		prec;

	prec = (flags >> 35) & 0xFF;
	width = (flags >> 27) & 0xFF;
	s = 0;
	if (type == 0x1 || type == 0x2)
		s = (flags >> 20) & 1 && prec < strsize ? prec : strsize;
	else if (type >= 0x4 && type <= 0x400)
		s = prec > strsize ? prec : strsize;
	else if (type == 0x800)
		s = strsize;
	s = width > s ? width : s;
	if ((type == 0x8 || type == 0x10) && prec > 0 && !width)
	{
		s = ((flags >> 24) & 0x1) && !((flags >> 25) & 0x1) ? s + 15 : s;
		s = !((flags >> 24) & 0x1) && ((flags >> 25) & 0x1) ? s + 100 : s;
	}
	return ((flags >> 2) & 1 ? s + 2 : s);
}

/*
** Function : ft_process_width2
** --------------------------------
** @param str : string to cat in c width time
** @param c : can be '0' or ' ', char to be cat in string width time
** @param width : cat c in string a number of time
** @return the string with the good number of '0' or ' '
*/

char			*ft_process_width2(char *str, char *c, int width)
{
	if (width > 0)
		while (width-- > 0)
			ft_strcat(str, c);
	return (str);
}

/*
** Function : ft_process_prec2
** -----------------------------
** @param ans : string in which the good the number of char will be cut
** @param prec : number of wanted char to print
** @param flags : every flags parsed
** @return the culled string
*/

char			*ft_process_prec2(char *ans, int prec, uint64_t flags)
{
	int j;

	j = 0;
	if (((flags & 0xFFF) >= 0x4) && ((flags >> 25) & 1))
		while (prec-- > 0)
			ft_strcat(ans, "0");
	else if (((flags & 0xFFF) == 0x1) && ((flags >> 25) & 1))
		ans[prec] = '\0';
	else if (((flags & 0xFFF) == 0x2) && ((flags >> 25) & 1))
	{
		if (ans[prec] >> 7)
			while (((ans[prec] >> 6) & 0x3) != 3 && prec > 0)
				prec--;
		ans[prec] = '\0';
	}
	return (ans);
}

/*
** Function ft_newlist
** ---------------------
** @param content pointer to string
** @param size size of the string
** @param is_malloc needed for easy free
** @return the created link
*/

t_string		*ft_newlist(void *content, int size, size_t is_malloc)
{
	t_string *maillon;

	if (!(maillon = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	maillon->next = NULL;
	maillon->content = content;
	maillon->content_size = size;
	maillon->is_malloc = is_malloc;
	return (maillon);
}

/*
** Function : ft_wcharstr
** --------------------------
** @param c : wchar_t who will be transformed into char *
** @return fresh malloced string
*/

char			*ft_wcharstr(wchar_t c)
{
	char	*str;

	str = ft_strnew(ft_wcharlen(c));
	if (c <= 0x7F)
		str[0] = c;
	else if (c <= 0x7FF)
	{
		str[0] = ((c >> 6) | 0xC0);
		str[1] = ((c & 0x3F) | 0x80);
	}
	else if (c <= 0xFFFF)
	{
		str[0] = ((c >> 12) | 0xE0);
		str[1] = (((c >> 6) & 0x3F) | 0x80);
		str[2] = ((c & 0x3F) | 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		str[0] = ((c >> 18) | 0xF0);
		str[1] = (((c >> 12) & 0x3F) | 0x80);
		str[2] = (((c >> 6) & 0x3F) | 0x80);
		str[3] = ((c & 0x3F) | 0x80);
	}
	return (str);
}
