/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_param.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:11:10 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:24:50 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		get_ind_p(t_asm *a, t_param *p)
{
	int i;

	p->type = T_IND;
	p->size = 2;
	if (a->ln.line[0] == LABEL_CHAR)
	{
		i = 0;
		while (a->ln.line[i] != ' ' && a->ln.line[i] != '\0')
			i++;
		p->label = ft_strsub(a->ln.line, 1, i - 1);
	}
	else
		p->val = ft_atoi(a->ln.line);
}

static void		get_reg_p(t_asm *a, t_param *p)
{
	a->ln.line++;
	p->type = T_REG;
	p->size = 1;
	p->val = ft_atoi(a->ln.line);
}

static void		get_dir_p(t_asm *a, t_param *p, int op)
{
	int i;

	a->ln.line++;
	p->type = T_DIR;
	p->size = 4 - g_op_tab[op - 1].dir_size_two * 2;
	if (a->ln.line[0] == LABEL_CHAR)
	{
		i = 0;
		while (a->ln.line[i] != ' ' && a->ln.line[i] != '\0')
			i++;
		p->label = ft_strsub(a->ln.line, 1, i - 1);
	}
	else
		p->val = ft_atoi(a->ln.line);
}

static void		init_p(t_param *p)
{
	p->val = 0;
	p->size = 0;
	p->type = 0;
	p->label = NULL;
}

void			get_param(t_asm *a, t_param *p, int op)
{
	if (!is_valid_p(a->ln.line))
	{
		ft_printf("Line %d : Invalid parameter\n", a->ln.nb, a->ln.line);
		free_all(a);
	}
	init_p(p);
	if (a->ln.line[0] == DIRECT_CHAR)
		get_dir_p(a, p, op);
	else if (a->ln.line[0] == 'r')
		get_reg_p(a, p);
	else
		get_ind_p(a, p);
}
