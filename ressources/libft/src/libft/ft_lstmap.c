/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:20:51 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:33:11 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp = f(lst);
	if (lst->next)
		tmp->next = ft_lstmap(lst->next, f);
	return (tmp);
}
