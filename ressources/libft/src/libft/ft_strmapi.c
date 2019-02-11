/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:26:08 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:28:58 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	char	*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(str = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	if (s && f)
	{
		while (s[i] != '\0')
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
