/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op4.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 15:31:02 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 13:38:51 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_and(t_vm *vm, t_proc *p, t_ocp *o, int op)
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
	p->reg[o->v_tr - 1] = val_u & val_d;
	p->carry = !p->reg[o->v_tr - 1];
	if (vm->flags & 0x04)
		ft_printf("P%s%5d | %s %d %d r%d\n", ((p->id >= 10000) ? " " : ""),\
		p->id, g_opname[op - 1], val_u, val_d, o->v_tr);
	if (vm->flags & 0x10)
		verbose_mvt(vm, p, o->s_de + o->s_tr + o->s_un + 2);
}
