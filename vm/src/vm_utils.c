/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 12:46:39 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:54:19 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

int		nb(char **av)
{
	int nb;
	int i;
	int j;

	i = -1;
	nb = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '.' && av[i][j + 1] == 'c' && av[i][j + 2] == 'o'
					&& av[i][j + 3] == 'r' && av[i][j + 4] == '\0')
			{
				nb++;
				break ;
			}
		}
	}
	return (nb);
}

void	dump_arena(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i && i % 64 == 0)
			ft_printf("\n0x%.4x : ", i);
		ft_printf("%.2x ", vm->arena[i]);
		i++;
	}
	ft_printf("\n");
}

int		read_bytes(t_vm *vm, int size, int i)
{
	int res;

	res = 0;
	while (i < 0)
		i += MEM_SIZE;
	if (i >= MEM_SIZE)
		i %= MEM_SIZE;
	while (--size)
	{
		res |= vm->arena[i++];
		if (i == MEM_SIZE)
			i = 0;
		res <<= 8;
	}
	res |= vm->arena[i];
	return (res);
}

void	vm_decrement_cycles(t_vm *vm)
{
	if (vm->nb_live >= NBR_LIVE)
	{
		vm->max_cycle -= CYCLE_DELTA;
		vm->last_check = 0;
		if (vm->flags & 0x02)
			ft_printf("Cycle to die is now %d\n", vm->max_cycle);
	}
	else
	{
		vm->last_check++;
		if (vm->last_check >= MAX_CHECKS)
		{
			vm->max_cycle -= CYCLE_DELTA;
			vm->last_check = 0;
			if (vm->flags & 0x02)
				ft_printf("Cycle to die is now %d\n", vm->max_cycle);
		}
	}
	vm->nb_live = 0;
}
