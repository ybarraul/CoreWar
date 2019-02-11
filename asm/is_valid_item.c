/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_valid_item.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:16:27 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:25:46 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid_label_char(char c)
{
	const char	*s = LABEL_CHARS;
	int			j;

	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int			is_valid_label(char *line, int i_stop)
{
	int i;

	i = 0;
	if (i_stop > 0)
	{
		while (i < i_stop)
		{
			if (!is_valid_label_char(line[i]))
				return (0);
			i++;
		}
	}
	else if (i_stop == -1)
	{
		while (line[i] != ' ' && line[i] != '\0')
		{
			if (!is_valid_label_char(line[i]))
				return (0);
			i++;
		}
	}
	if (i == 0)
		return (0);
	return (1);
}

static int	is_valid_reg(char *line)
{
	int i;

	i = 0;
	if (!(line[i + 1] >= '0' && line[i + 1] <= '9'))
		return (0);
	if (!(line[i + 2] == ' ' || line[i + 2] == '\0'))
	{
		if (!(line[i + 2] >= '0' && line[i + 2] <= '9'))
			return (0);
		if (!(line[i + 3] == ' ' || line[i + 3] == '\0'))
			return (0);
	}
	if (!(ft_atoi(&(line[i + 1])) >= 0 && ft_atoi(&(line[i + 1])) <= 99))
		return (0);
	return (1);
}

int			is_valid_p(char *line)
{
	int i;

	i = 0;
	if (line[i] == 'r')
		return (is_valid_reg(line));
	else
	{
		if (line[i] == DIRECT_CHAR)
			i++;
		if (line[i] == LABEL_CHAR)
			return (is_valid_label(&(line[i + 1]), -1));
		if (line[i] == '-')
			i++;
		if (line[i] == ' ' || line[i] == '\0')
			return (0);
		while (line[i] != ' ' && line[i] != '\0')
		{
			if (!(line[i] >= '0' && line[i] <= '9'))
				return (0);
			i++;
		}
	}
	return (1);
}
