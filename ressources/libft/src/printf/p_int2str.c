/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   p_int2str.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/16 03:13:03 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/16 03:13:03 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static char		*p_type_d(void *val, uint64_t *flags)
{
	char	*ans;

	ans = NULL;
	if ((*flags >> 14) & 1 && (*flags & 0xF) == 0x8)
		ans = ft_itoa_base((char)val, 10);
	else if ((*flags >> 13) & 1 && (*flags & 0xF) == 0x8)
		ans = ft_itoa_base((short int)val, 10);
	else if (((*flags >> 12) & 0xFF) == 0 && (*flags & 0xF) == 0x8)
		ans = ft_itoa_base((int)val, 10);
	else if ((*flags >> 4) & 1 || ((*flags >> 3) & 1 && (*flags >> 15) & 1))
		ans = ft_itoa_base((long)val, 10);
	else if ((*flags >> 16) & 1)
		ans = ft_itoa_base((long long)val, 10);
	else if ((*flags >> 17) & 1)
		ans = ft_itoa_base((intmax_t)val, 10);
	else if ((*flags >> 18) & 1)
		ans = ft_itoa_base((ssize_t)val, 10);
	else if ((*flags >> 19) & 1)
		ans = ft_itoa_base((ptrdiff_t)val, 10);
	*flags = (*flags >> 4) & 1 ? (*flags & 0xffffffffffffffef) | 0x8 : *flags;
	return (ans);
}

static char		*p_type_o(void *val, const uint64_t flags)
{
	char	*ans;

	ans = NULL;
	if ((flags >> 14) & 1 && (flags >> 5) & 1)
		ans = ft_uitoa_base((unsigned char)val, 8);
	else if ((flags >> 13) & 1 && (flags >> 5) & 1)
		ans = ft_uitoa_base((unsigned short int)val, 8);
	else if (((flags >> 12) & 0xFF) == 0 && (flags >> 5) & 1)
		ans = ft_uitoa_base((unsigned int)val, 8);
	else if (((flags >> 6) & 1) || ((flags >> 5) & 1 && (flags >> 15) & 1))
		ans = ft_uitoa_base((unsigned long)val, 8);
	else if ((flags >> 16) & 1)
		ans = ft_uitoa_base((unsigned long long)val, 8);
	else if ((flags >> 17) & 1)
		ans = ft_uitoa_base((uintmax_t)val, 8);
	else if ((flags >> 18) & 1)
		ans = ft_uitoa_base((size_t)val, 8);
	else if ((flags >> 19) & 1)
		ans = ft_uitoa_base((ptrdiff_t)val, 8);
	return (ans);
}

static char		*p_type_u(void *val, const uint64_t flags)
{
	char		*ans;
	uintmax_t	i;

	i = (uintmax_t)val;
	ans = NULL;
	if ((flags >> 14) & 1 && (flags >> 7) & 1)
		ans = ft_uitoa_base((unsigned char)i, 10);
	else if ((flags >> 13) & 1 && (flags >> 7) & 1)
		ans = ft_uitoa_base((unsigned short int)i, 10);
	else if (((flags >> 12) & 0xFF) == 0 && (flags >> 7) & 1)
		ans = ft_uitoa_base((unsigned int)i, 10);
	else if ((flags >> 8) & 1 || ((flags >> 7) & 1 && (flags >> 15) & 1))
		ans = ft_uitoa_base((unsigned long)i, 10);
	else if ((flags >> 16) & 1)
		ans = ft_uitoa_base((unsigned long long)i, 10);
	else if ((flags >> 17) & 1)
		ans = ft_uitoa_base((uintmax_t)i, 10);
	else if ((flags >> 18) & 1)
		ans = ft_uitoa_base((size_t)i, 10);
	else if ((flags >> 19) & 1)
		ans = ft_uitoa_base((ptrdiff_t)i, 10);
	return (ans);
}

static	char	*p_type_x(void *val, const uint64_t flags)
{
	char	*ans;

	if ((flags >> 2) & 1 && (intmax_t)val != 0)
		ans = ft_uitoa_base((uintmax_t)val, 16);
	else if ((flags >> 2) & 1 && (intmax_t)val == 0)
		ans = ft_uitoa_base((unsigned int)val, 16);
	else if ((flags >> 14) & 1 && (flags >> 9) && 1)
		ans = ft_uitoa_base((unsigned char)val, 16);
	else if ((flags >> 13) & 1 && (flags >> 9) && 1)
		ans = ft_uitoa_base((unsigned short int)val, 16);
	else if (((flags >> 12) & 0xFF) == 0 && ((flags >> 9) && 1))
		ans = ft_uitoa_base((unsigned int)val, 16);
	else if ((flags >> 10) & 1 || ((flags >> 9) & 1 && (flags >> 15) & 1))
		ans = ft_uitoa_base((unsigned long)val, 16);
	else if ((flags >> 16) & 1)
		ans = ft_uitoa_base((unsigned long long)val, 16);
	else if ((flags >> 17) & 1)
		ans = ft_uitoa_base((uintmax_t)val, 16);
	else if ((flags >> 18) & 1)
		ans = ft_uitoa_base((size_t)val, 16);
	else
		ans = ft_uitoa_base((ptrdiff_t)val, 16);
	return (ans);
}

t_string		*p_int2str(void *val, uint64_t flags)
{
	char	*ans;

	ans = NULL;
	if ((uintmax_t)val == 0 && ((flags >> 25) & 1 && !((flags >> 35) & 0xFF))\
	&& !((flags >> 20) & 1))
		ans = ft_strdup("");
	else if ((uintmax_t)val == 0 && ((flags >> 25) & 1 && !((flags >> 35) &\
	0xFF)) && ((flags >> 20) & 1) && (((flags >> 9) & 1) || (flags >> 10) & 1))
		ans = ft_strdup("");
	else if ((flags >> 3) & 1 || (flags >> 4) & 1)
		ans = p_type_d(val, &flags);
	else if ((flags >> 5) & 1 || (flags >> 6) & 1)
		ans = p_type_o(val, flags);
	else if ((flags >> 7) & 1 || (flags >> 8) & 1)
		ans = p_type_u(val, flags);
	else if ((flags >> 9) & 1 || (flags >> 10) & 1 || (flags >> 2) & 1)
		ans = p_type_x(val, flags);
	ans = p_int(ans, flags, ((flags >> 35) & 0xFF), 0);
	(flags >> 9) & 1 || (flags >> 2) & 1 ? ft_str_tolower(ans) : ans;
	return (ft_newlist(ans, ft_strlen(ans), 1));
}
