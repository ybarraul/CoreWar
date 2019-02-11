/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:57:38 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 03:49:04 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_atoi(const char *str)
{
	int neg;
	int res;

	res = 0;
	neg = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n' ||
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * neg);
}
