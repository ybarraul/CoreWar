/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_game.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 11:56:04 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 13:41:22 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	do_proc_action(t_proc *p, t_vm *vm)
{
	if (p->wait > 0)
		p->wait--;
	else
	{
		if (p->wait == 0)
		{
			p->wait = -1;
			if (p->next_op == -1)
				p->next_op = vm->arena[p->pc];
			is_valid_op(vm, p);
			p->next_op = -1;
		}
		else if (vm->arena[p->pc] >= 0x01 && vm->arena[p->pc] <= 0x10)
		{
			p->wait = vm->op_timer[vm->arena[p->pc] - 1] - 2;
			p->next_op = vm->arena[p->pc];
		}
		else
			p->pc++;
		if (p->pc == MEM_SIZE)
			p->pc = 0;
	}
}

static void	vm_play(t_vm *vm)
{
	t_proc *p;

	vm->cur_cycle = 0;
	while (vm->cur_cycle < vm->max_cycle)
	{
		if (vm->flags & 0x20 && vm->tot_cycle == vm->dump_cycle + 1)
		{
			dump_arena(vm);
			vm_free(vm);
			exit(0);
		}
		if (vm->flags & 0x02)
			ft_printf("It is now cycle %d\n", vm->tot_cycle);
		p = vm->proc;
		while (p != NULL)
		{
			do_proc_action(p, vm);
			p = p->next;
		}
		vm->cur_cycle++;
		vm->tot_cycle++;
	}
}

static void	vm_killprocwithfire(t_vm *vm, t_proc *p)
{
	while (p != NULL)
	{
		if (p->alive)
		{
			p->last_live = p->alive;
			p->alive = 0;
			p = p->next;
		}
		else
		{
			if (vm->flags & 0x08)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						p->id, vm->tot_cycle - p->last_live - 1, vm->max_cycle);
			if (p->next != NULL)
			{
				p = p->next;
				del_proc(vm, &(vm->proc), p->last);
			}
			else
			{
				del_proc(vm, &(vm->proc), p);
				p = NULL;
			}
		}
	}
}

static void	last_turn_op(t_vm *vm)
{
	t_proc		*p;

	p = vm->proc;
	while (p != NULL)
	{
		if (p->wait == 0)
		{
			if (p->next_op == -1)
				p->next_op = vm->arena[p->pc];
			is_valid_op(vm, p);
			p->wait = -1;
			p->alive = 0;
			if (p->next_op == 1)
				p->last_live = vm->tot_cycle;
		}
		p = p->next;
	}
}

void		vm_game(t_vm *vm)
{
	int			stop;

	stop = 0;
	while (vm->proc_nb)
	{
		vm_play(vm);
		if (!stop && vm->max_cycle <= 0)
		{
			if (vm->flags & 0x02)
				ft_printf("It is now cycle %d\n", vm->tot_cycle);
			last_turn_op(vm);
			vm->tot_cycle++;
			stop = 1;
		}
		vm_killprocwithfire(vm, vm->proc);
		vm_decrement_cycles(vm);
	}
}
