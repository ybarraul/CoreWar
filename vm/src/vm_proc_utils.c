/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_proc_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 11:33:53 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 18:57:34 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

static void		free_in_case_it_fucks_up(t_vm *vm, t_proc **start)
{
	if (!start)
		solo_exit("Memory allocation for new processus failed", vm);
	while (*start)
		del_proc(vm, start, *start);
	solo_exit("Memory allocation for new processus failed", vm);
}

void			new_proc(t_vm *vm, t_proc **start, int player_id, int pc)
{
	static unsigned int		nb = 1;
	int						i;
	t_proc					*new;

	i = 0;
	if (!(new = ft_memalloc(sizeof(t_proc))))
		free_in_case_it_fucks_up(vm, start);
	new->id = nb;
	new->player_id = player_id;
	new->pc = pc;
	while (new->pc < 0)
		new->pc += MEM_SIZE;
	if (new->pc >= MEM_SIZE)
		new->pc %= MEM_SIZE;
	new->alive = 0;
	new->last_live = 0;
	new->wait = -1;
	new->next_op = -1;
	new->next = *start;
	if (*start != NULL)
		(*start)->last = new;
	new->last = NULL;
	*start = new;
	nb++;
	vm->proc_nb++;
}

void			del_proc(t_vm *vm, t_proc **start, t_proc *proc)
{
	t_proc *next;
	t_proc *last;

	next = proc->next;
	last = proc->last;
	if (last)
		last->next = next;
	if (next)
		next->last = last;
	if (proc == *start)
	{
		if (next)
			*start = next;
		else
			*start = NULL;
	}
	free(proc);
	vm->proc_nb--;
}

void			cpy_proc(t_proc *src, t_proc *dst)
{
	int i;

	i = 0;
	while (i < 16)
	{
		dst->reg[i] = src->reg[i];
		i++;
	}
	dst->alive = src->alive;
	dst->carry = src->carry;
	dst->last_live = src->last_live;
}
