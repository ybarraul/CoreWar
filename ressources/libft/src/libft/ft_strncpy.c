/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:26:50 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:26:54 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	char		*tmp;

	tmp = dest;
	if (n != 0)
	{
		while (n && *src)
		{
			*dest++ = *src++;
			n--;
		}
		while (n-- > 0)
			*dest++ = '\0';
	}
	return (tmp);
}
