/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_op.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:25:15 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:49:34 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		get_op(t_asm *a)
{
	int i;

	i = 15;
	while (i >= 0)
	{
		if (!ft_strncmp(a->ln.line, g_op_tab[i].s_op,
					(int)ft_strlen(g_op_tab[i].s_op)))
			return (i + 1);
		i--;
	}
	ft_printf("Line %d : Wrong operation |%s|\n", a->ln.nb, a->ln.line);
	free_all(a);
	return (-1);
}

static int		fill_param(t_param *p_ope, t_asm *a, int op, int p_nb)
{
	t_param p;

	get_param(a, &p, op);
	while (a->ln.line[0] != ' ' && a->ln.line[0] != '\0')
		a->ln.line++;
	p_ope->val = p.val;
	p_ope->size = p.size;
	p_ope->type = p.type;
	p_ope->label = p.label;
	if ((g_op_tab[op - 1].opc[p_nb - 1] & p_ope->type) == 0)
	{
		ft_printf("Line %d : Wrong parameter type for operation |%s|\n",
				a->ln.nb, g_op_tab[op - 1].s_op);
		p_ope->size = -99;
	}
	return (p_ope->size);
}

static void		init_params(t_ope *ope)
{
	t_param empty_p;

	empty_p.val = 0;
	empty_p.size = 0;
	empty_p.type = 0;
	empty_p.label = NULL;
	ft_memcpy(&(ope->p_un), &empty_p, sizeof(t_param));
	ft_memcpy(&(ope->p_de), &empty_p, sizeof(t_param));
	ft_memcpy(&(ope->p_tr), &empty_p, sizeof(t_param));
}

static int		check_params(t_asm *a, int op)
{
	int		param;
	t_ope	ope;

	ope.op = op;
	ope.opc = g_op_tab[op - 1].has_opc;
	init_params(&ope);
	ope.size = 1 + ope.opc;
	ope.size += fill_param(&ope.p_un, a, op, 1);
	param = 1;
	while (++param <= g_op_tab[op - 1].op_arg)
	{
		if (a->ln.line[0] != ' ' || a->ln.line[1] != ','
				|| a->ln.line[2] != ' ')
		{
			ft_printf("Line %d : Missing parameter\n", a->ln.nb);
			free_all(a);
		}
		a->ln.line += 3;
		if (param == 2)
			ope.size += fill_param(&ope.p_de, a, op, param);
		else
			ope.size += fill_param(&ope.p_tr, a, op, param);
	}
	lst_ope_push(a, &ope);
	return (ope.size);
}

int				check_op(t_asm *a)
{
	int nb_bytes;
	int op;

	op = get_op(a);
	a->ln.line += (int)ft_strlen(g_op_tab[op - 1].s_op);
	if (a->ln.line[0] != ' ')
	{
		ft_printf("Line %d : Missing space after operation |%s|\n",
				a->ln.nb, a->ln.line - (int)ft_strlen(g_op_tab[op - 1].s_op));
		free_all(a);
	}
	a->ln.line++;
	nb_bytes = check_params(a, op);
	while (a->ln.line[0] == ' ')
		a->ln.line++;
	if (nb_bytes <= 1 || a->ln.line[0] != '\0')
	{
		ft_printf("Line %d : Error in parameters\n", a->ln.nb);
		free_all(a);
	}
	return (nb_bytes);
}
