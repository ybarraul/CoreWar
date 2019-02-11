/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:21:08 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 03:17:20 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newl;

	if (!(newl = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		newl->content = NULL;
		newl->content_size = 0;
	}
	else
	{
		if (!(newl->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(newl->content, content, content_size);
		newl->content_size = content_size;
	}
	newl->next = NULL;
	return (newl);
}
