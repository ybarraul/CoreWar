/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/30 07:45:25 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/30 07:45:25 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strndup(const char *s, size_t len)
{
	size_t		i;
	char		*dst;

	i = 0;
	if (!(dst = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
