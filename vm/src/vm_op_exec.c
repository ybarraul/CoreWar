/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_op_exec.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 15:22:17 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 16:34:55 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

static void		exec_op2(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (op == 11)
		op_sti(vm, p, o, op);
	else if (op == 12)
		op_fork(vm, p, o, op);
	else if (op == 13)
		op_lld(vm, p, o, op);
	else if (op == 14)
		op_lldi(vm, p, o, op);
	else if (op == 15)
		op_lfork(vm, p, o, op);
	else if (op == 16)
		op_aff(vm, p, o);
}

void			exec_op(t_vm *vm, t_proc *p, t_ocp *o, int op)
{
	if (op > 10)
		exec_op2(vm, p, o, op);
	else if (op == 1)
		op_live(vm, p, o, op);
	else if (op == 2)
		op_ld(vm, p, o, op);
	else if (op == 3)
		op_st(vm, p, o, op);
	else if (op == 4)
		op_add(vm, p, o, op);
	else if (op == 5)
		op_sub(vm, p, o, op);
	else if (op == 6)
		op_and(vm, p, o, op);
	else if (op == 7)
		op_or(vm, p, o, op);
	else if (op == 8)
		op_xor(vm, p, o, op);
	else if (op == 9)
		op_zjmp(vm, p, o, op);
	else if (op == 10)
		op_ldi(vm, p, o, op);
}
