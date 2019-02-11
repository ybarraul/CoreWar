/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_processing_infos.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/10 19:08:20 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 16:46:00 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_string		*p_pointer(wchar_t *val, uint64_t flags)
{
	char	*ans;
	char	*tmp;

	tmp = NULL;
	ans = NULL;
	if (val != NULL && ((flags & 0xf) == 2 || (flags >> 15) & 1))
	{
		tmp = ft_strnew(ft_wstrlen(val));
		tmp = ft_process_wcharstring(tmp, val);
	}
	else if (val != NULL && ((flags & 0xf) == 1))
		tmp = ft_strdup((char *)val);
	else if (val == NULL)
		tmp = ft_strdup("(null)");
	ft_process_prec2(tmp, ((flags >> 35) & 0xFF), flags);
	if (tmp)
	{
		ans = p_string(tmp, flags, (flags >> 21) & 1 ? "0" : " ",\
		(flags >> 27) & 0xFF);
		free(tmp);
	}
	if (!ans)
		return (ft_newlist(NULL, -1, 0));
	return (ft_newlist(ans, ft_strlen(ans), 1));
}

t_string		*p_char(wchar_t val, const uint64_t flags)
{
	char	*ans;
	char	*str;
	int		width;
	int		i;

	if (val <= 255 && val > 127 && (str = ft_strnew(1)))
		str[0] = -2;
	else if (ft_wcharlen(val) == 0 || (val >= 0xD800 && val <= 0xDFFF) ||\
	ft_wcharlen(val) > (unsigned long)MB_CUR_MAX)
		return (ft_newlist(NULL, -1, 0));
	else if (val == 0)
		str = NULL;
	else
		str = ft_wcharstr(val);
	i = !str ? 1 : ft_strlen(str);
	ans = ft_strnew(ft_calc_size(i, flags, (int)(flags & 0xFFF)));
	width = ((flags >> 27) & 0xFF) - i;
	if (!((flags >> 22) & 1))
		ans = ft_process_width2(ans, ((flags >> 21) & 1) ? "0" : " ", width);
	str ? ans = ft_strcat(ans, str) : 0;
	if ((flags >> 22) & 1)
		ans = ft_process_width2(ans, " ", str ? width : width + 1);
	!str && (flags >> 22) & 1 ? ans[0] = '\0' : 0;
	str ? free(str) : 0;
	return (ft_newlist(ans, width > 0 ? width + i : i, 1));
}

static void		ft_va_arg(void **val, va_list ap, const uint64_t flags)
{
	if ((flags & 0xFFF) <= 0x4 || (flags & 0xFFF) == 0x800)
		*val = va_arg(ap, void *);
	else if ((flags & 0xFFF) <= 0x400)
		*val = (void *)va_arg(ap, intmax_t);
}

t_string		*p_infos(va_list ap, const uint64_t flags)
{
	void		*val;
	t_string	*ans;

	ans = NULL;
	if ((flags >> 12) & 1 && (ans = p_char(L'%', flags)))
		return (ans);
	ft_va_arg(&val, ap, flags);
	if (((flags & 0xFFF) >= 0x4) && ((flags & 0xFFF) <= 0x400))
		ans = p_int2str(val, flags);
	else if (((flags & 0xF) < 0x4) && ((flags & 0xF) > 0))
		ans = p_pointer((wchar_t *)val, flags);
	else if (((flags & 0x800) == 0x800))
		return (p_char((wchar_t)val, flags));
	else if ((flags & 0xFFF) == 0)
		ans = ft_newlist(ft_strdup(""), 1, 1);
	return (ans);
}
