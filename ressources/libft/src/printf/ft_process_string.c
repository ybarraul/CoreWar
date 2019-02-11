/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_process_string.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 16:40:04 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 13:23:42 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char		*p_string(char *val, uint64_t flags, char *c, int width)
{
	char	*ans;
	size_t	len;

	len = ft_strlen(val);
	width -= len;
	ans = ft_strnew(ft_calc_size(len, flags, (flags & 0xFFF)));
	if (!((flags >> 22) & 1))
		ans = ft_process_width2(ans, c, width);
	ans = ft_strcat(ans, val);
	if ((flags >> 22) & 1)
		ans = ft_process_width2(ans, c, width);
	return (ans);
}

char		*ft_process_wcharstring(char *ans, wchar_t *val)
{
	char	*tmp;

	while (*val != '\0')
	{
		if (ft_wcharlen(*val) == 0 || (*val >= 0xD800 && *val <= 0xDFFF))
			break ;
		if (ft_wcharlen(*val) > (unsigned long)MB_CUR_MAX)
		{
			tmp = ft_strnew(1);
			tmp[0] = -2;
		}
		else
			tmp = ft_wcharstr(*val);
		ft_strcat(ans, tmp);
		free(tmp);
		val++;
	}
	if (*val != '\0')
	{
		free(ans);
		ans = NULL;
	}
	return (ans);
}
