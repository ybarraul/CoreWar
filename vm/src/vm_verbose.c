/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_verbose.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 16:33:06 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:20:17 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	verbose_mvt(t_vm *vm, t_proc *p, int mvt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", mvt, p->pc_origin,\
	p->pc_origin + mvt);
	while (i < mvt)
	{
		if (i + p->pc_origin >= MEM_SIZE)
			ft_printf("%.2x ", vm->arena[(i + p->pc_origin) % MEM_SIZE]);
		else if (i + p->pc_origin < 0)
		{
			j = MEM_SIZE;
			while (i + p->pc_origin + j < 0)
				j += MEM_SIZE;
			ft_printf("%.2x ", vm->arena[i + p->pc_origin + j]);
		}
		else
			ft_printf("%.2x ", vm->arena[i + p->pc_origin]);
		i++;
	}
	ft_printf("\n");
}
