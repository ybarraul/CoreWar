/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 20:02:10 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/12 21:31:02 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

double			ft_sqrt(double nb)
{
	double		sqrt;

	if (nb == -0)
		return (-0);
	sqrt = 0;
	while (sqrt * sqrt < nb)
		sqrt++;
	return (sqrt);
}
