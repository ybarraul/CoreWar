/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strisalphanum.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 04:44:18 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 04:44:18 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

bool	check_ifalphanum(char *to_check)
{
	int		i;
	bool	check;

	i = 0;
	check = true;
	while (check && to_check[i] != '\0')
	{
		if (!ft_isalnum(to_check[i]))
			check = false;
		i++;
	}
	return (check);
}
