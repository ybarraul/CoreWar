/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/26 14:08:30 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/12 21:31:20 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_realloc(void *var, size_t last, size_t size)
{
	void	*tmp;

	if (!(tmp = malloc(size)))
		return (NULL);
	ft_bzero(tmp, size);
	ft_memcpy(tmp, var, last < size ? last : size);
	free(var);
	return (tmp);
}
