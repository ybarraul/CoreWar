/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   err_exit.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 15:03:19 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 15:03:19 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

void	string_exit(char *msg, char *param, t_vm *vm)
{
	ft_printf("%s : %s\n", msg, param);
	vm_free(vm);
	exit(1);
}

void	solo_exit(char *msg, t_vm *vm)
{
	ft_printf("%s\n", msg);
	vm_free(vm);
	exit(1);
}
