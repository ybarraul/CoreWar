/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_champinfo.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 17:36:16 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 15:52:36 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		champinfo_err(t_asm *a, char *s, int num, int fd)
{
	if (num == 0)
		ft_printf("Line %d : Missing \" after %s command\n", a->ln.nb, s);
	else if (num == 1)
		ft_printf("Line %d : Champion's %s is too long !\n", a->ln.nb, s);
	else
		ft_printf("%s is missing terminating \" !", s);
	close(fd);
	free_all(a);
}

static void		champinfo_char_after_quote(t_asm *a, int i, char *s)
{
	while (a->ln.line[i] == ' ' || (a->ln.line[i] >= 9 && a->ln.line[i] <= 13))
		i++;
	if (!(a->ln.line[i] == '\0' || a->ln.line[i] == '#'
				|| (SEMI_COLON_OK && a->ln.line[i] == ';')))
	{
		ft_printf("Line %d : Wrong characters after %s |%s|\n",
				a->ln.nb, s, &(a->ln.line[i]));
		free_all(a);
	}
}

static void		get_champ_comment(t_asm *a, int fd)
{
	int i;

	a->ln.line += (int)ft_strlen(COMMENT_CMD_STRING);
	while (a->ln.line[0] == ' ' || (a->ln.line[0] >= 9 && a->ln.line[0] <= 13))
		a->ln.line++;
	if (a->ln.line[0] != '"')
		champinfo_err(a, COMMENT_CMD_STRING, 0, fd);
	a->ln.line++;
	i = 0;
	while (i < COMMENT_LENGTH && a->ln.line[i] != '\0')
	{
		a->h.comment[i] = a->ln.line[i];
		if (a->ln.line[i] == '"')
			break ;
		i++;
	}
	if (i == COMMENT_LENGTH && a->ln.line[i] != '"')
		champinfo_err(a, COMMENT_CMD_STRING, 1, fd);
	if (a->ln.line[i] != '"')
		champinfo_err(a, COMMENT_CMD_STRING, 2, fd);
	champinfo_char_after_quote(a, i + 1, COMMENT_CMD_STRING);
	while (i <= COMMENT_LENGTH)
		a->h.comment[i++] = '\0';
}

static void		get_champ_name(t_asm *a, int fd)
{
	int i;

	a->ln.line += (int)ft_strlen(NAME_CMD_STRING);
	while (a->ln.line[0] == ' ' || (a->ln.line[0] >= 9 && a->ln.line[0] <= 13))
		a->ln.line++;
	if (a->ln.line[0] != '"')
		champinfo_err(a, NAME_CMD_STRING, 0, fd);
	a->ln.line++;
	i = 0;
	while (i < PROG_NAME_LENGTH && a->ln.line[i] != '\0')
	{
		a->h.prog_name[i] = a->ln.line[i];
		if (a->ln.line[i] == '"')
			break ;
		i++;
	}
	if (i == PROG_NAME_LENGTH && a->ln.line[i] != '"')
		champinfo_err(a, NAME_CMD_STRING, 1, fd);
	if (a->ln.line[i] != '"')
		champinfo_err(a, NAME_CMD_STRING, 2, fd);
	champinfo_char_after_quote(a, i + 1, NAME_CMD_STRING);
	while (i <= PROG_NAME_LENGTH)
		a->h.prog_name[i++] = '\0';
}

void			get_champ_info(t_asm *a, int fd)
{
	if (!ft_strncmp(a->ln.line, NAME_CMD_STRING,
				(int)ft_strlen(NAME_CMD_STRING)))
		get_champ_name(a, fd);
	else if (!ft_strncmp(a->ln.line, COMMENT_CMD_STRING,
				(int)ft_strlen(COMMENT_CMD_STRING)))
		get_champ_comment(a, fd);
	else
	{
		ft_printf("Line %d : Unknown command |%s|", a->ln.nb, a->ln.line);
		free_all(a);
	}
}
