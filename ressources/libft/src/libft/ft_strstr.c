/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:27:43 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:27:45 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	char *s1;
	char *s2;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && haystack)
	{
		if (*haystack == *needle)
		{
			s1 = (char *)haystack;
			s2 = (char *)needle;
			while (*s1 && *s2 && *s1 == *s2)
			{
				s1++;
				s2++;
			}
			if (!*s2)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
