/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strclr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 02:23:50 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/11/23 02:23:51 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_strclr(char *s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
		s[i++] = '\0';
}
