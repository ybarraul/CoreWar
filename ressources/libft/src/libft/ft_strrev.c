/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/25 10:48:22 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/26 14:26:52 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strrev(const char *s)
{
	char	*str;
	char	*tmp;

	if (!(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	tmp = str;
	s = s + ft_strlen(s) - 1;
	while (*s)
		*str++ = *s--;
	return (tmp);
}
