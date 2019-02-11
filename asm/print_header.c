/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_header.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:50:15 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:30:13 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	print_text(int fd_dest, char *text, int size)
{
	int		pad;
	char	s[1];

	s[0] = '\0';
	write(fd_dest, text, size);
	pad = 4 - size % 4;
	while (pad != 0)
	{
		write(fd_dest, s, 1);
		pad--;
	}
}

static void	print_uint(int fd_dest, unsigned int i)
{
	char s[4];

	s[0] = i >> 24;
	s[1] = i >> 16;
	s[2] = i >> 8;
	s[3] = i;
	write(fd_dest, s, 4);
}

void		print_header(t_asm *a, int fd_dest)
{
	print_uint(fd_dest, a->h.magic);
	print_text(fd_dest, a->h.prog_name, PROG_NAME_LENGTH + 1);
	print_uint(fd_dest, a->h.prog_size);
	print_text(fd_dest, a->h.comment, COMMENT_LENGTH + 1);
}
