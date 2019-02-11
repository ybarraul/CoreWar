/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 15:30:15 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 13:39:12 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_or(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int val_u;
	int val_d;

	if (o->t_un == REG_CODE)
		val_u = p->reg[o->v_un - 1];
	else if (o->t_un == DIR_CODE)
		val_u = o->v_un;
	else
		val_u = read_bytes(vm, DIR_SIZE, p->pc_origin + (short int)o->v_un\
		% IDX_MOD);
	if (o->t_de == REG_CODE)
		val_d = p->reg[o->v_de - 1];
	else if (o->t_de == DIR_CODE)
		val_d = o->v_de;
	else
		val_d = read_bytes(vm, DIR_SIZE, p->pc_origin + (short int)o->v_de\
		% IDX_MOD);
	p->reg[o->v_tr - 1] = val_u | val_d;
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], val_u, val_d, o->v_tr);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_xor(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int val_u;
	int val_d;

	if (o->t_un == REG_CODE)
		val_u = p->reg[o->v_un - 1];
	else if (o->t_un == DIR_CODE)
		val_u = o->v_un;
	else
		val_u = read_bytes(vm, DIR_SIZE, p->pc_origin + (short int)o->v_un\
		% IDX_MOD);
	if (o->t_de == REG_CODE)
		val_d = p->reg[o->v_de - 1];
	else if (o->t_de == DIR_CODE)
		val_d = o->v_de;
	else
		val_d = read_bytes(vm, DIR_SIZE, p->pc_origin + (short int)o->v_de\
		% IDX_MOD);
	p->reg[o->v_tr - 1] = val_u ^ val_d;
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], val_u, val_d, o->v_tr);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_zjmp(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (p->carry)
	{
		p->pc = p->pc_origin + (short int)o->v_un % IDX_MOD;
		while (p->pc < 0)
			p->pc += MEM_SIZE;
		if (p->pc >= MEM_SIZE)
			p->pc %= MEM_SIZE;
	}
	if (vm->flags & 0x04)
	{
		if (p->carry)
			ft_printf("P%s%5d | %s %d %s\n", ((p->id >= 10000) ? " " : ""),\
			p->id, g_opname[op - 1], (short int)o->v_un, "OK");
		else
		{
			ft_printf("P%s%5d | %s %d %s\n", ((p->id >= 10000) ? " " : ""),\
			p->id, g_opname[op - 1], (short int)o->v_un, "FAILED");
			if (vm->flags & 0x10)
				verbose_mvt(vm, p, 3);
		}
	}
}

void	op_ldi(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int val_u;
	int val_d;
	int sum;

	val_u = (short int)o->v_un;
	if (o->t_un == REG_CODE)
		val_u = p->reg[o->v_un - 1];
	else if (o->t_un == IND_CODE)
		val_u = read_bytes(vm, REG_SIZE, p->pc_origin + o->v_un % IDX_MOD);
	val_d = (short int)o->v_de;
	if (o->t_de == REG_CODE)
		val_d = p->reg[o->v_de - 1];
	else if (o->t_de == IND_CODE)
		val_d = read_bytes(vm, REG_SIZE, p->pc_origin + o->v_de % IDX_MOD);
	sum = read_bytes(vm, REG_SIZE, p->pc_origin + (val_u + val_d) % IDX_MOD);
	p->reg[o->v_tr - 1] = sum;
	if (vm->flags & 0x04)
	{
		ft_printf("P%s%5d | %s %d %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], val_u, val_d, o->v_tr);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",\
		val_u, val_d, val_u + val_d, p->pc_origin + (val_u + val_d) % IDX_MOD);
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}

void	op_sti(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int val_d;
	int val_t;

	val_d = (short int)o->v_de;
	if (o->t_de == REG_CODE)
		val_d = p->reg[o->v_de - 1];
	else if (o->t_de == IND_CODE)
		val_d = read_bytes(vm, REG_SIZE, p->pc_origin + val_d % IDX_MOD);
	val_t = (short int)o->v_tr;
	if (o->t_tr == REG_CODE)
		val_t = p->reg[o->v_tr - 1];
	write_on_arena(vm, p->reg[o->v_un - 1],\
	p->pc_origin + (val_d + val_t) % IDX_MOD);
	if (vm->flags & 0x04)
	{
		ft_printf("P%s%5d | %s r%d %d %d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], o->v_un, val_d, val_t);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",\
		val_d, val_t, val_d + val_t, p->pc_origin + (val_d + val_t) % IDX_MOD);
	}
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}
