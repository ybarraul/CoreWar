/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_copy_tab.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 07:42:21 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 07:42:21 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
** Function : copy_tab
** @param tab
** @return
*/

char		**copy_tab(char **tab)
{
	int			i;
	char		**buf;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	if (!(buf = ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		buf[i] = ft_strdup(tab[i]);
		i++;
	}
	return (buf);
}
