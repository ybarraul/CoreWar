/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 15:04:32 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:54:09 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_op			g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};

void			free_all(t_asm *a)
{
	lst_lab_del_all(a);
	lst_ope_del_all(a);
	free(a->ln.lfree);
	exit(1);
}

static void		init_asm(t_asm *a)
{
	a->lst_lab = NULL;
	a->lst_ope = NULL;
	a->h.magic = COREWAR_EXEC_MAGIC;
	a->h.prog_name[0] = -1;
	a->h.comment[0] = -1;
	a->h.prog_size = 0;
	a->ln.nb = 0;
	a->ln.size = 256;
	a->ln.line = NULL;
	a->ln.lfree = NULL;
	a->ln.line = malloc(a->ln.size);
	if (a->ln.line == NULL)
	{
		perror("Memory allocation on line failed");
		exit(1);
	}
	a->ln.lfree = a->ln.line;
}

static char		*get_dst_name(t_asm *a, char *src_file)
{
	char *dst_file;

	dst_file = malloc((int)ft_strlen(src_file) + 3);
	if (dst_file == NULL)
	{
		perror("Memory allocation failed on .cor file name");
		free_all(a);
	}
	ft_strcpy(dst_file, src_file);
	dst_file[(int)ft_strlen(dst_file) - 1] = '\0';
	ft_strcat(dst_file, "cor");
	return (dst_file);
}

static void		create_cor_file(t_asm *a, char *file)
{
	int		fd_dest;
	char	*dst_file;

	dst_file = get_dst_name(a, file);
	fd_dest = open(dst_file, O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd_dest < 0)
	{
		perror("Could not create .cor file");
		close(fd_dest);
		free(dst_file);
		free_all(a);
	}
	print_header(a, fd_dest);
	print_cor(a, fd_dest);
	close(fd_dest);
	free(dst_file);
}

int				main(int argc, char **argv)
{
	t_asm a;

	verif_valid_arg(argc, argv);
	init_asm(&a);
	read_file(&a, argv[1]);
	fill_label_val(&a);
	create_cor_file(&a, argv[1]);
	free_all(&a);
	return (0);
}
