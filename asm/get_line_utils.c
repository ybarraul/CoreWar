/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_line_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/15 12:45:23 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:54:01 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void		realloc_line(t_asm *a, int i)
{
	if (i >= a->ln.size)
	{
		a->ln.line = a->ln.lfree;
		a->ln.line = realloc(a->ln.line, a->ln.size * 2);
		a->ln.lfree = a->ln.line;
		a->ln.size *= 2;
		if (a->ln.line == NULL)
		{
			perror("Malloc error on line reallocation");
			free_all(a);
		}
	}
}

static void	ignore_multiple_space(t_asm *a)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (a->ln.line[i] != '\0')
	{
		if (i && a->ln.line[i] == ' ' && a->ln.line[i - 1] == ' ')
			j++;
		a->ln.line[i - j] = a->ln.line[i];
		i++;
	}
	if (i && a->ln.line[i - 1] == ' ')
		i--;
	a->ln.line[i - j] = '\0';
}

int			sanitize_line(t_asm *a, int res, int i)
{
	if (res < 0)
	{
		perror("Error reading file");
		free_all(a);
	}
	a->ln.line[i] = '\0';
	if (a->ln.line[0] != '.')
		ignore_multiple_space(a);
	return (1);
}
