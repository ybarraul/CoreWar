/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:28:00 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:28:48 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strtrim(char const *s)
{
	int		st;
	size_t	end;
	char	*str;

	if (!s)
		return (NULL);
	st = 0;
	end = ft_strlen(s) - 1;
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st] != '\0')
		st++;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && (int)end > st)
		end--;
	if (!(str = ft_strnew(end - st + 1)))
		return (NULL);
	str = ft_strsub(s, st, (int)end - st + 1);
	return (str);
}
