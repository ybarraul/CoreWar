/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_process_int.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/19 20:17:17 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 20:02:34 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			ft_process_plus(char *ans, char *str, uint64_t flags, int width)
{
	int		zero;
	int		signe;
	int		moins;

	zero = (flags >> 21) & 1;
	moins = (flags >> 22) & 1;
	signe = str[0] == '-' ? '-' : '+';
	if (((flags & 0xfff) >= 0x80 && (flags & 0xfff) <= 0xf400) || (flags >> 2)\
	& 1 || (flags >> 5) & 1 || (flags >> 6) & 1)
		return ;
	else if (width > 0 && !zero && !moins && signe == '+')
		ans[width - 1] = signe;
	else if (((width > 0 && moins) || (width <= 0 && !moins)) && signe == '+')
	{
		width = 0;
		while (ans[width] != ' ' && ans[width] != '\0')
			width++;
		while (width-- > 0)
			ans[width + 1] = ans[width];
		ans[0] = signe;
	}
	else if (zero && width > 0 && (ans[0] = signe) == signe)
		if (signe == '-' && (ans = ft_strchr(ans + 1, '-')))
			*ans = '0';
}

/*
** Function : ft_process_shieet
** -----------------------------------
** @param ans : string a modifier
** @param f : flags
** @param w : width
** @param z : flag zero
** @param m : flag moins
*/

void			ft_process_shit(char *ans, uint64_t f, int w, int z)
{
	int		m;

	m = (f >> 22) & 1;
	if (!z && !m && w > 0 && ((f >> 9) & 1 || (f >> 10) & 1 || (f >> 2) & 1))
	{
		ans[w - 1] = 'X';
		ans[w - 2] = '0';
	}
	else if (!z && !m && w > 0 && ((f >> 5) & 1 || (f >> 6) & 1))
		ans[w - 1] = '0';
	else if (z && !((f >> 5) & 1 || (f >> 6) & 1) && w > 0)
		ans[1] = 'X';
	else
	{
		w = 0;
		z = (f >> 5) & 1 || (f >> 6) & 1 ? 1 : 2;
		while (ans[w] != ' ' && ans[w] != '\0')
			w++;
		while (w-- >= 0)
			ans[w + z] = ans[w];
		if ((f >> 9) & 1 || (f >> 10) & 1 || (f >> 2) & 1)
			ans[1] = 'X';
		ans[0] = '0';
	}
}

static void		ft_calc_wp(char *str, uint64_t flags, size_t *prec, int *width)
{
	size_t i;

	i = ft_strlen(str);
	*prec += *str == '-' ? 1 : 0;
	*prec = *prec > i ? *prec : i;
	*width = ((flags >> 27) & 0xFF) - *prec;
	if ((flags >> 24) & 1)
		*width -= 1;
	if (*width == 1 && (((flags >> 5) & 1 || (flags >> 6) & 1)) &&\
	(flags >> 21) & 1)
		*width = 0;
}

static char		*ft_place_moins(char *ans, char *str)
{
	int i;
	int j;

	i = 0;
	while (ans[i] == ' ')
		i++;
	j = i;
	if (str && str[0] == '-' && ans[i] == '0')
	{
		while (ans[i] != '-')
			i++;
		ans[j] = '-';
		ans[i] = '0';
	}
	free(str);
	return (ans);
}

char			*p_int(char *str, uint64_t flags, size_t prec,\
								int width)
{
	char		*ans;

	ft_calc_wp(str, flags, &prec, &width);
	ans = ft_strnew(1 + ft_calc_size(ft_strlen(str), flags, (flags & 0xFFF)));
	if (((flags >> 24) & 1) && !((flags >> 23) & 1) && *str != '-'\
	&& ((flags >> 3) & 1 || (flags >> 4) & 1))
		ans = ft_strcat(ans, " ");
	if (!((flags >> 22) & 1))
		ans = ft_process_width2(ans, (flags >> 21) & 1 ? "0" : " ", width);
	ans = ft_process_prec2(ans, prec - ft_strlen(str), flags);
	ans = ft_strcat(ans, str);
	if ((flags >> 22) & 1)
		ans = ft_process_width2(ans, " ", width);
	if ((flags >> 23) & 1 || (*str == '-' && width > 0 && !((flags >> 22) & 1)))
		ft_process_plus(ans, str, flags, width);
	if (*str && ((flags >> 2) & 1 || (flags >> 5) & 1 || (flags >> 6) & 1 ||\
	(flags >> 9) & 1 || (flags >> 10) & 1) && (flags >> 20) & 1 && *str != '0')
		ft_process_shit(ans, flags, width, (flags >> 21) & 1);
	if ((flags >> 2) & 1)
		ft_process_shit(ans, flags, width, (flags >> 21) & 1);
	return (ft_place_moins(ans, str));
}
