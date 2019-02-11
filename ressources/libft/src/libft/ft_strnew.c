/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:27:10 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:27:11 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strnew(size_t size)
{
	char *str;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	ft_strclr(str);
	return (str);
}
