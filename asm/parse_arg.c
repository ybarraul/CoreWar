/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_arg.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 15:07:07 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:32:26 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	verif_s_file(char *arg)
{
	int i;

	i = (int)ft_strlen(arg);
	if (!(arg[i - 1] == 's' && arg[i - 2] == '.'))
	{
		ft_printf("Argument must have extension '.s'\n");
		exit(1);
	}
}

static void	verif_valid(int argc, char *arg)
{
	if (argc != 2)
	{
		if (argc < 2)
			ft_printf("Not enough arguments\nusage: ./asm source.s\n");
		if (argc > 2)
			ft_printf("Too many arguments\nusage: ./asm source.s\n");
		exit(1);
	}
	if ((int)ft_strlen(arg) < 3)
	{
		ft_printf("Argument must have '.s' extension\nusage: ./asm source.s\n");
		exit(1);
	}
}

void		verif_valid_arg(int argc, char **argv)
{
	verif_valid(argc, argv[1]);
	verif_s_file(argv[1]);
}
