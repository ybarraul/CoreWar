/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:27:18 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 15:54:57 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while ((j < len) && (needle[i] != '\0' || haystack[j] != '\0'))
	{
		if (needle[i] == haystack[j])
		{
			i++;
			j++;
		}
		else
		{
			j = j - i + 1;
			i = 0;
		}
		if (needle[0] == '\0')
			return ((char *)haystack);
		if (needle[i] == '\0')
			return ((char *)&haystack[j - i]);
		if (haystack[j] == '\0' || haystack[0] == '\0')
			return (0);
	}
	return (0);
}
