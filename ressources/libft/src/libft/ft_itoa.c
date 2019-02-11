/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:02:57 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/25 15:48:22 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t		ft_count_nb(int n)
{
	size_t		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (++i);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void			ft_putnbr_str(char *s, int n, int index)
{
	if (n < 0)
	{
		s[0] = '-';
		ft_putnbr_str(s, -n, index - 1);
	}
	else if (n < 10)
	{
		s[index] = n + '0';
	}
	else
	{
		ft_putnbr_str(s, n / 10, index - 1);
		s[index] = n % 10 + '0';
	}
}

char				*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	if (n == 0)
	{
		str = ft_strdup("0");
		return (str);
	}
	i = ft_count_nb(n);
	if (!(str = ft_strnew(i)))
		return (NULL);
	if (n > 0)
		ft_putnbr_str(str, n, i - 1);
	else
		ft_putnbr_str(str, n, i);
	str[i] = '\0';
	return (str);
}
