/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strisdigit.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 04:43:19 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 04:43:19 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

bool	check_ifdigit(char *to_check)
{
	bool	check;

	check = true;
	while (*to_check && check)
	{
		if (!ft_isdigit(*to_check++))
			check = false;
	}
	return (check);
}
