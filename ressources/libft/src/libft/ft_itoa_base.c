/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 21:47:38 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/14 01:46:30 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_itoa_base(intmax_t value, int base)
{
	char	*s;
	long	n;
	int		sign;
	int		i;

	if (value == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	if (base > 16 || base < 2)
		return (0);
	n = (value < 0) ? -(long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	if (!(s = ft_strnew(i + 1)))
		return (0);
	n = (value < 0) ? -(long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}

char	*ft_uitoa_base(uintmax_t value, int base)
{
	char		*s;
	uintmax_t	n;
	int			i;

	n = value;
	i = 1;
	if (base > 16 || base < 2)
		return (0);
	while ((value /= base) >= 1)
		i++;
	if (!(s = ft_strnew(i + 1)))
		return (0);
	while (i--)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	return (s);
}
