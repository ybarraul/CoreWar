/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 17:40:31 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 14:03:24 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_live(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int i;

	i = 0;
	p->alive = vm->tot_cycle;
	vm->nb_live++;
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], o->v_un);
	while (i < vm->nb_players)
	{
		if (o->v_un == vm->players[i].p_id)
		{
			vm->winner = i;
			if (vm->flags & 0x01)
				ft_printf("Player %d (%s) is said to be alive\n",\
				-vm->players[i].p_id, vm->players[i].prog_name);
			break ;
		}
		i++;
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, 5);
}

void	op_ld(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	p->reg[o->v_de - 1] = o->v_un;
	if (o->t_un == IND_CODE)
		p->reg[o->v_de - 1] = read_bytes(vm, DIR_SIZE, p->pc_origin +\
		(short int)o->v_un % IDX_MOD);
	p->carry = !p->reg[o->v_de - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], p->reg[o->v_de - 1], o->v_de);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_st(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (o->t_de == REG_CODE)
		p->reg[o->v_de - 1] = p->reg[o->v_un - 1];
	else
		write_on_arena(vm, p->reg[o->v_un - 1],\
		p->pc_origin + (short int)o->v_de % IDX_MOD);
	if (vm->flags & 0x04)
	{
		if (o->t_de == REG_CODE)
			ft_printf("P%s%5d | %s r%d %d\n", ((p->id >= 10000) ? " " : ""),\
			p->id, g_opname[op - 1], o->v_un, o->v_de);
		else
			ft_printf("P%s%5d | %s r%d %d\n", ((p->id >= 10000) ? " " : ""),\
			p->id, g_opname[op - 1], o->v_un, (short int)o->v_de);
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_add(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	p->reg[o->v_tr - 1] = p->reg[o->v_un - 1] + p->reg[o->v_de - 1];
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s r%d r%d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], o->v_un, o->v_de, o->v_tr);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_sub(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	p->reg[o->v_tr - 1] = p->reg[o->v_un - 1] - p->reg[o->v_de - 1];
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s r%d r%d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], o->v_un, o->v_de, o->v_tr);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}
