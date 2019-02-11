/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:24:23 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:29:27 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strcpy(char *dest, const char *src)
{
	char *tmp;

	tmp = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (tmp);
}
