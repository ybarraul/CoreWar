/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_parse_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 16:55:34 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 16:55:34 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

unsigned int	swap_bytes(unsigned int byte)
{
	unsigned int a;
	unsigned int b;

	a = byte & 0xffff;
	b = (byte & 0xffff0000) >> 16;
	a = ((a & 0xff) << 8) | ((a & 0xff00) >> 8);
	b = ((b & 0xff) << 8) | ((b & 0xff00) >> 8);
	return ((a << 16) | b);
}

int				check_dot_cor(char *str)
{
	int		len;
	char	*last_four;

	len = ft_strlen(str);
	if (len <= 4)
		return (0);
	last_four = &str[len - 4];
	return (!ft_strcmp(last_four, ".cor"));
}

int				check_ifstrdigit(char *to_check)
{
	int	check;

	check = 1;
	while (*to_check && check)
	{
		if (*to_check < '0' || *to_check > '9' || *to_check == '+' ||\
		*to_check == '-')
			check = 0;
		to_check++;
	}
	return (check);
}

static int		verif_valid_ocp2(t_ocp *o, int op)
{
	if (op == 6 || op == 7 || op == 8)
	{
		return (check_p(o->t_un, 1, 1, 1) && check_p(o->t_de, 1, 1, 1) &&
				check_p(o->t_tr, 1, 0, 0));
	}
	if (op == 10 || op == 14)
	{
		return (check_p(o->t_un, 1, 1, 1) && check_p(o->t_de, 1, 1, 0) &&
				check_p(o->t_tr, 1, 0, 0));
	}
	if (op == 11)
	{
		return (check_p(o->t_un, 1, 0, 0) && check_p(o->t_de, 1, 1, 1) &&
				check_p(o->t_tr, 1, 1, 0));
	}
	if (op == 16)
	{
		return (check_p(o->t_un, 1, 0, 0) && check_p(o->t_de, 0, 0, 0) &&
				check_p(o->t_tr, 0, 0, 0));
	}
	return (1);
}

int				verif_valid_ocp(t_ocp *o, int op)
{
	if (op == 2 || op == 13)
	{
		return (check_p(o->t_un, 0, 1, 1) && check_p(o->t_de, 1, 0, 0) &&
				check_p(o->t_tr, 0, 0, 0));
	}
	if (op == 3)
	{
		return (check_p(o->t_un, 1, 0, 0) && check_p(o->t_de, 1, 0, 1) &&
				check_p(o->t_tr, 0, 0, 0));
	}
	if (op == 4 || op == 5)
	{
		return (check_p(o->t_un, 1, 0, 0) && check_p(o->t_de, 1, 0, 0) &&
				check_p(o->t_tr, 1, 0, 0));
	}
	return (verif_valid_ocp2(o, op));
}
