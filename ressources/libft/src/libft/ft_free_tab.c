/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_tab.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 02:24:22 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 02:24:22 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	free_tab(void **tab)
{
	void	*head;

	head = tab;
	if (tab)
	{
		while (*tab)
			ft_memdel(&(*tab++));
		ft_memdel(&head);
	}
}
