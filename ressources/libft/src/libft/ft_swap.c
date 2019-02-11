/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/25 15:50:07 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/26 14:26:12 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	void	*c;

	if (!(c = ft_memalloc(size)))
		return ;
	ft_memcpy(c, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, c, size);
	free(c);
}
