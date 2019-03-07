/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:41:54 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:57:57 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		open_file(t_asm *a, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening source file");
		free_all(a);
	}
	return (fd);
}

static void		verif_valid_file(t_asm *a, int oct_nb)
{
	if (oct_nb == 0)
	{
		ft_printf("File is empty...\n");
		free_all(a);
	}
	if (a->h.prog_name[0] == -1)
	{
		ft_printf("Champion's name missing...");
		free_all(a);
	}
	if (a->h.comment[0] == -1)
	{
		ft_printf("Champion's comment missing...");
		free_all(a);
	}
}

void			read_file(t_asm *a, char *file)
{
	int fd;
	int oct_nb;

	fd = open_file(a, file);
	oct_nb = 0;
	while ((a->ln.line = a->ln.lfree) && readline(a, fd))
	{
		if (a->ln.line[0] == '.')
		{
			get_champ_info(a, fd);
			continue;
		}
		else if (a->ln.line[0] == '\0')
			continue;
		a->ln.line += check_label(a, oct_nb);
		if (a->ln.line[0] == '\0')
			continue;
		oct_nb += check_op(a);
	}
	close(fd);
	a->h.prog_size = oct_nb;
	verif_valid_file(a, oct_nb);
}
