/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 13:29:14 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:40:20 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_fork(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	new_proc(vm, &(vm->proc), p->player_id,\
	(p->pc_origin + (short int)o->v_un % IDX_MOD) % MEM_SIZE);
	cpy_proc(p, vm->proc);
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d (%d)\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], (short int)o->v_un,\
		p->pc_origin + (short int)o->v_un % IDX_MOD);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, 3);
}

void	op_lld(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int res;
	int i;

	res = 0;
	if (o->t_un == IND_CODE)
	{
		i = (p->pc_origin + o->v_un) % MEM_SIZE;
		res |= vm->arena[i++];
		i %= MEM_SIZE;
		res <<= 8;
		res |= vm->arena[i++];
		res = (short int)res < 0 ? res | 0xffff0000 : res & 0x0000ffff;
		p->reg[o->v_de - 1] = res;
	}
	else if (o->t_un == DIR_CODE)
		p->reg[o->v_de - 1] = o->v_un;
	p->carry = !p->reg[o->v_de - 1];
	if (vm->flags & 0x04 && o->t_un == IND_CODE)
		ft_printf("P%s%5d | %s %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], res, o->v_de);
	else if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], o->v_un, o->v_de);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_lldi(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int val_u;
	int val_d;

	val_u = (short int)o->v_un;
	if (o->t_un == REG_CODE)
		val_u = p->reg[o->v_un - 1];
	else if (o->t_un == IND_CODE)
		val_u = read_bytes(vm, REG_SIZE, p->pc_origin + (short int)o->v_un %\
		IDX_MOD);
	val_d = (short int)o->v_de;
	if (o->t_de == REG_CODE)
		val_d = p->reg[o->v_de - 1];
	p->reg[o->v_tr - 1] = read_bytes(vm, REG_SIZE,\
			p->pc_origin + (val_u + val_d));
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
	{
		ft_printf("P%s%5d | %s %d %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], val_u, val_d, o->v_tr);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",\
				val_u, val_d, val_u + val_d, p->pc_origin + (val_u + val_d));
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_lfork(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int f_adr;

	f_adr = p->pc_origin + (short int)o->v_un;
	while (f_adr < 0)
		f_adr += MEM_SIZE;
	if (f_adr >= MEM_SIZE)
		f_adr %= MEM_SIZE;
	new_proc(vm, &(vm->proc), p->player_id, f_adr);
	cpy_proc(p, vm->proc);
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d (%d)\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1],\
		(short int)o->v_un, p->pc_origin + (short int)o->v_un);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, 3);
}

void	op_aff(t_vm *vm, t_proc *p, t_ocp *o)
{
	if (vm->flags & 0x40)
	{
		ft_putstr("Aff: ");
		ft_putchar(p->reg[o->v_un - 1] % 256);
		ft_putstr("\n");
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, 3);
}
