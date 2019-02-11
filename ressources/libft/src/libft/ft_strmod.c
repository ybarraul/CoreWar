/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmod.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 21:24:02 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/22 02:57:06 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmod(char *src, const char *sw, const char *del, char delim)
{
	char	*res;
	char	*str;
	int		intdelim;

	if (!(res = ft_strnew(ft_strlen(src) + ft_strlen(sw) - ft_strlen(del))))
		return (NULL);
	str = ft_strchr(src, delim);
	intdelim = str - src;
	res = ft_strncpy(res, src, intdelim);
	res = ft_strcat(res, sw);
	if (!ft_strncmp(str, del, ft_strlen(del)))
		str += ft_strlen(del);
	res = ft_strcat(res, str);
	free(src);
	return (res);
}
