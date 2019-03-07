/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 16:47:30 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 13:19:42 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

char g_opname[16][10] =
{
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff",
};

static	void		usage(void)
{
	ft_printf("Usage : [-dump N -v N -a] [[-n N] <champion1.cor>]\n\n"\
				"################### TEXT OUTPUT MODE ###################\n\n"\
				"-a : for Aff\n"
				"-n N : choose the player number for the next player\n"
				"-dump N : dump memory after N cycles then exit\n"\
				"-v N : verbosity level, can be added to enable several\n"\
				"     - 1 : Show lives\n"\
				"     - 2 : Show cycles\n"\
				"     - 4 : Show operations\n"\
				"     - 8 : Show deaths\n"\
				"     - 16 : Show PC movements\n");
	exit(1);
}

void				vm_free(t_vm *vm)
{
	free(vm->arena);
	while (vm->proc)
		del_proc(vm, &vm->proc, vm->proc);
}

int					main(int argc, char **argv)
{
	t_vm	vm;
	int		i;

	i = 0;
	if (argc < 2)
		usage();
	vm_init(&vm);
	ft_printf("Introducing contestants...\n");
	vm_parse(&vm, &argv[1]);
	vm.winner = vm.nb_players - 1;
	while (i < vm.nb_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
		i + 1, vm.players[i].prog_size, vm.players[i].prog_name,\
		vm.players[i].comment);
		i++;
	}
	vm_game(&vm);
	ft_printf("Contestant %d, \"%s\", has won !\n",\
	vm.winner + 1, vm.players[vm.winner].prog_name);
	vm_free(&vm);
	return (0);
}
