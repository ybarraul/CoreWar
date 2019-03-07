/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_label.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 18:38:31 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:58:35 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		has_label(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			return (-1);
		if (line[i] == LABEL_CHAR)
			return (i);
		i++;
	}
	return (-1);
}

static int		check_valid_char(char *line, int end, const char *char_list)
{
	int i;
	int j;
	int j_len;

	j_len = (int)ft_strlen(char_list);
	i = 0;
	while (i < end)
	{
		j = 0;
		while (j < j_len)
		{
			if (line[i] == char_list[j])
				break ;
			j++;
		}
		if (j == j_len)
			return (0);
		i++;
	}
	return (1);
}

int				check_label(t_asm *a, int pos)
{
	int label_end;

	label_end = has_label(a->ln.line);
	if (label_end == -1)
		return (0);
	if (!label_end || !check_valid_char(a->ln.line, label_end, LABEL_CHARS))
	{
		ft_printf("Line %d : Wrong label |%s|\n", a->ln.nb, a->ln.line);
		free_all(a);
	}
	lst_lab_push(a, ft_strsub(a->ln.line, 0, label_end), pos);
	while (a->ln.line[label_end + 1] == ' ')
		label_end++;
	return (label_end + 1);
}
