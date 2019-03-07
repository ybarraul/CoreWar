/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_line.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 15:52:59 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:56:25 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		clean_separators(t_asm *a, char buf, int i)
{
	if (a->ln.line[0] != '.')
	{
		if (buf == SEPARATOR_CHAR)
		{
			realloc_line(a, i + 3);
			a->ln.line[i++] = ' ';
			a->ln.line[i++] = SEPARATOR_CHAR;
			a->ln.line[i++] = ' ';
		}
		else
		{
			a->ln.line[i] = buf;
			i++;
			realloc_line(a, i);
		}
	}
	else
	{
		a->ln.line[i] = buf;
		i++;
		realloc_line(a, i);
	}
	return (i);
}

static int		escape_comments(t_asm *a, int fd, char *buf)
{
	if (a->ln.line[0] != '.'
			&& (buf[0] == '#' || (SEMI_COLON_OK && buf[0] == ';')))
	{
		while (read(fd, buf, 1) && buf[0] != '\n' && buf[0] != '\0')
			buf[0] = '\0';
		return (1);
	}
	return (0);
}

static void		init_readline(t_asm *a, int *stop, int *i)
{
	a->ln.nb++;
	*stop = 0;
	*i = 0;
	a->ln.line[0] = '\0';
}

int				readline(t_asm *a, int fd)
{
	int		res;
	int		i;
	char	buf[1];
	int		stop;

	init_readline(a, &stop, &i);
	if ((res = read(fd, buf, 1)) == 0)
		return (0);
	while (res > 0 && buf[0] != '\0')
	{
		if (a->ln.line[0] == '.' && buf[0] == '"')
			stop++;
		if ((buf[0] == '\n' && (a->ln.line[0] != '.'
						|| stop >= 2)) || escape_comments(a, fd, buf))
			break ;
		else if (buf[0] == '\n')
			a->ln.nb++;
		if (a->ln.line[0] != '.' && (buf[0] >= 9 && buf[0] <= 13))
			buf[0] = ' ';
		if (!(i == 0 && buf[0] == ' '))
			i = clean_separators(a, buf[0], i);
		res = read(fd, buf, 1);
	}
	return (sanitize_line(a, res, i));
}
