/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 15:04:54 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:20:00 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	read_ocp(t_ocp *o, unsigned char ocp, int no_ocp)
{
	if (no_ocp)
		return ;
	if ((ocp & 0b11000000) == 0b11000000)
		o->t_un = IND_CODE;
	else if ((ocp & 0b01000000) == 0b01000000)
		o->t_un = REG_CODE;
	else if ((ocp & 0b10000000) == 0b10000000)
		o->t_un = DIR_CODE;
	if ((ocp & 0b00110000) == 0b00110000)
		o->t_de = IND_CODE;
	else if ((ocp & 0b00010000) == 0b00010000)
		o->t_de = REG_CODE;
	else if ((ocp & 0b00100000) == 0b00100000)
		o->t_de = DIR_CODE;
	if ((ocp & 0b00001100) == 0b00001100)
		o->t_tr = IND_CODE;
	else if ((ocp & 0b00000100) == 0b00000100)
		o->t_tr = REG_CODE;
	else if ((ocp & 0b00001000) == 0b00001000)
		o->t_tr = DIR_CODE;
}

int		check_p(int param, int r, int d, int i)
{
	if (r && param == REG_CODE)
		return (1);
	if (d && param == DIR_CODE)
		return (1);
	if (i && param == IND_CODE)
		return (1);
	if (!r && !d && !i)
		return (1);
	return (0);
}

int		get_params_size(t_ocp *o, int op)
{
	int dir_size;

	dir_size = DIR_SIZE;
	if (op == 9 || op == 10 || op == 11 || op == 12 || op == 14 || op == 15)
		dir_size = 2;
	if (o->t_un == REG_CODE)
		o->s_un = 1;
	else if (o->t_un == DIR_CODE)
		o->s_un = dir_size;
	else if (o->t_un == IND_CODE)
		o->s_un = IND_SIZE;
	if (o->t_de == REG_CODE)
		o->s_de = 1;
	else if (o->t_de == DIR_CODE)
		o->s_de = dir_size;
	else if (o->t_de == IND_CODE)
		o->s_de = IND_SIZE;
	if (o->t_tr == REG_CODE)
		o->s_tr = 1;
	else if (o->t_tr == DIR_CODE)
		o->s_tr = dir_size;
	else if (o->t_tr == IND_CODE)
		o->s_tr = IND_SIZE;
	return (o->s_un + o->s_de + o->s_tr);
}

void	bla(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (op == 1 || op == 9 || op == 12 | op == 15)
		read_ocp(o, 0, 1);
	else
	{
		read_ocp(o, vm->arena[p->pc++], 0);
		if (p->pc == MEM_SIZE)
			p->pc = 0;
	}
	if (op == 2 || op == 3 || op == 13 || op == 16)
		o->t_tr = 0;
	if (op == 16)
		o->t_de = 0;
}

int		is_valid_op(t_vm *vm, t_proc *p)
{
	t_ocp	o;
	int		op;
	int		p_size;

	ft_bzero(&o, sizeof(t_ocp));
	p->pc_origin = p->pc;
	op = vm->arena[p->pc++];
	op = p->next_op;
	if (p->pc == MEM_SIZE)
		p->pc = 0;
	bla(vm, p, &o, op);
	p_size = get_params_size(&o, op);
	if (!verif_valid_ocp(&o, op))
	{
		if (vm->flags & 0x10)
			verbose_mvt(vm, p, p_size + 2);
		p->pc += p_size;
		p->pc %= MEM_SIZE;
		return (0);
	}
	read_params(vm, p, &o, op);
	return (1);
}
