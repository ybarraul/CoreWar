/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op_read_params.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:52:20 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:19:31 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

int		read_special_p(t_vm *vm, t_proc *p, int op)
{
	int size;

	size = 2;
	if (op == 1)
		size = 4;
	return (read_p(vm, p, size));
}

int		read_p(t_vm *vm, t_proc *p, int size)
{
	int res;

	res = 0;
	while (p->pc < 0)
		p->pc += MEM_SIZE;
	if (p->pc >= MEM_SIZE)
		p->pc %= MEM_SIZE;
	else if (p->pc < 0)
		p->pc += MEM_SIZE;
	while (size > 1)
	{
		res ^= vm->arena[p->pc++];
		if (p->pc == MEM_SIZE)
			p->pc = 0;
		res <<= 8;
		size--;
	}
	if (size)
	{
		res ^= vm->arena[p->pc++];
		if (p->pc == MEM_SIZE)
			p->pc = 0;
	}
	return (res);
}

void	write_on_arena(t_vm *vm, int val, int adr)
{
	while (adr < 0)
		adr += MEM_SIZE;
	if (adr >= MEM_SIZE)
		adr %= MEM_SIZE;
	vm->arena[adr++] = (val >> 24) & 0xff;
	if (adr >= MEM_SIZE)
		adr %= MEM_SIZE;
	vm->arena[adr++] = (val >> 16) & 0xff;
	if (adr >= MEM_SIZE)
		adr %= MEM_SIZE;
	vm->arena[adr++] = (val >> 8) & 0xff;
	if (adr >= MEM_SIZE)
		adr %= MEM_SIZE;
	vm->arena[adr++] = val & 0xff;
}

void	read_op_params(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (op == 1 || op == 9 || op == 12 | op == 15)
		o->v_un = read_special_p(vm, p, op);
	else
	{
		o->v_un = read_p(vm, p, o->s_un);
		o->v_de = read_p(vm, p, o->s_de);
		o->v_tr = read_p(vm, p, o->s_tr);
	}
}

int		read_params(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	int i;

	i = p->pc_origin;
	read_op_params(vm, p, o, op);
	if ((o->t_un == REG_CODE && !(o->v_un >= 1 && o->v_un <= 16))
			|| (o->t_de == REG_CODE && !(o->v_de >= 1 && o->v_de <= 16))
			|| (o->t_tr == REG_CODE && !(o->v_tr >= 1 && o->v_tr <= 16)))
	{
		if (vm->flags & 0x10)
			verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
		return (0);
	}
	exec_op(vm, p, o, op);
	return (1);
}
