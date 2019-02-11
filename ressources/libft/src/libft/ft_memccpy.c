/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:21:26 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/25 18:37:15 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)src == (unsigned char)c)
		{
			*(unsigned char *)dst++ = *(unsigned char *)src;
			return (dst);
		}
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	return (NULL);
}
