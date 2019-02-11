/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 11:49:07 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 12:56:44 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** -Verifier que certains des macros ne sont pas mauvais
*/

static void		op_h_check(void)
{
	if (IND_SIZE < 1 || REG_SIZE < 1 || MEM_SIZE < 1 || CYCLE_DELTA < 1 ||\
		NBR_LIVE < 1 || MAX_CHECKS < 1 || REG_NUMBER < 1 || DIR_SIZE < 1)
	{
		ft_printf("wrong op.h\n");
		exit(-1);
	}
	if (REG_CODE == DIR_CODE || REG_CODE == IND_CODE || IND_CODE == DIR_CODE)
	{
		ft_printf("wrong op.h2\n");
		exit(-1);
	}
}

static void		vm_init2(t_vm *vm)
{
	vm->op_timer[0] = 10;
	vm->op_timer[1] = 5;
	vm->op_timer[2] = 5;
	vm->op_timer[3] = 10;
	vm->op_timer[4] = 10;
	vm->op_timer[5] = 6;
	vm->op_timer[6] = 6;
	vm->op_timer[7] = 6;
	vm->op_timer[8] = 20;
	vm->op_timer[9] = 25;
	vm->op_timer[10] = 25;
	vm->op_timer[11] = 800;
	vm->op_timer[12] = 10;
	vm->op_timer[13] = 50;
	vm->op_timer[14] = 1000;
	vm->op_timer[15] = 2;
}

void			vm_init(t_vm *vm)
{
	op_h_check();
	vm->arena = malloc(MEM_SIZE);
	ft_bzero(vm->arena, MEM_SIZE);
	if (!vm->arena)
	{
		perror("Memory allocation for arena failed\n");
		exit(-1);
	}
	vm->nb_live = 0;
	vm->proc_nb = 0;
	vm->flags = 0;
	vm->proc = NULL;
	vm->cur_cycle = 0;
	vm->max_cycle = CYCLE_TO_DIE;
	vm->dump_cycle = -1;
	vm->last_check = 0;
	vm->winner = 1;
	vm->nb_players = 0;
	vm_init2(vm);
	vm->last_check = 0;
	vm->tot_cycle = 1;
}
