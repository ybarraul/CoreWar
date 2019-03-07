/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_parse.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 16:09:19 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:55:06 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm.h"

static void				flag_verbose(t_vm *vm, char *av)
{
	int nb;

	nb = 0;
	if (!av)
		solo_exit("Error missing argument for verbose", vm);
	if (check_ifstrdigit(av) && (nb = ft_atoi(av)) >= 0)
		vm->flags |= (nb & 0x1f);
	else
		string_exit("Error bad verbose", av, vm);
}

static void				flag_dump(t_vm *vm, char *av)
{
	if (!av)
		solo_exit("Error missing argument for dump", vm);
	if (check_ifstrdigit(av))
	{
		if ((vm->dump_cycle = ft_atoi(av)) < 0)
			string_exit("Error bad dump", av, vm);
		vm->flags |= 0x20;
	}
	else
		string_exit("Error bad dump", av, vm);
}

static void				flag_pnum(char *av, int *pnum, t_vm *vm)
{
	int x;

	x = 0;
	if (!av)
		solo_exit("Error missing argument for dump", vm);
	if (check_ifstrdigit(av))
		x = -ft_atoi(av);
	else
		string_exit("Error wrong argument for -n", av, vm);
	if (x > -1)
		string_exit("Error -n needs positive numbers > 1", av, vm);
	if (x != 1 && x >= *pnum)
		string_exit("Error wrong player number for -n", av, vm);
	else
		*pnum = x;
}

static void				parse_cor(t_vm *vm, char *file, int pnum)
{
	static int		index = 0;
	int				fd;
	unsigned char	prog[CHAMP_MAX_SIZE];

	if ((fd = open(file, O_RDONLY)) == -1)
		string_exit("Error opening file", file, vm);
	read(fd, &vm->players[index], sizeof(t_header));
	if ((vm->players[index].magic =\
		swap_bytes(vm->players[index].magic)) != COREWAR_EXEC_MAGIC)
		solo_exit("Error wrong magic", vm);
	if ((vm->players[index].prog_size =\
		swap_bytes(vm->players[index].prog_size)) > CHAMP_MAX_SIZE)
		solo_exit("Error prog size too big", vm);
	ft_bzero(prog, CHAMP_MAX_SIZE);
	read(fd, &prog, CHAMP_MAX_SIZE);
	vm->players[index].p_id = pnum;
	ft_memcpy((void *)&(vm->arena[(MEM_SIZE / vm->nb_players) * index]),\
	(void *)prog, vm->players[index].prog_size);
	new_proc(vm, &(vm->proc), pnum, (MEM_SIZE / vm->nb_players) * index);
	vm->proc->reg[0] = vm->players[index].p_id;
	index++;
	close(fd);
}

void					vm_parse(t_vm *vm, char **av)
{
	int pnum;

	pnum = -1;
	vm->nb_players = nb(av);
	if (vm->nb_players < 1 || vm->nb_players > MAX_PLAYERS)
		solo_exit("Error too few or many players", vm);
	while (*av)
	{
		if (!ft_strcmp(*av, "-v"))
			flag_verbose(vm, *++av);
		else if (!ft_strcmp(*av, "-dump") || !ft_strcmp(*av, "-d"))
			flag_dump(vm, *++av);
		else if (!ft_strcmp(*av, "-n"))
			flag_pnum(*++av, &pnum, vm);
		else if (!ft_strcmp(*av, "-a"))
			vm->flags |= 0x40;
		else if (check_dot_cor(*av))
		{
			parse_cor(vm, *av, pnum);
			pnum--;
		}
		av++;
	}
}
