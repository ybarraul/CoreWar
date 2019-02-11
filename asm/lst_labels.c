/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_labels.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 18:41:59 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:26:09 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static t_lab	*lst_lab_new(t_asm *a, char *name, int pos)
{
	t_lab *new;

	new = malloc(sizeof(t_lab));
	if (new == NULL)
	{
		perror("Malloc on new label failed");
		free_all(a);
	}
	new->name = name;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void			lst_lab_push(t_asm *a, char *name, int pos)
{
	t_lab *crawler;
	t_lab *new;

	new = lst_lab_new(a, name, pos);
	if (a->lst_lab != NULL)
	{
		crawler = a->lst_lab;
		while (crawler->next != NULL)
			crawler = crawler->next;
		crawler->next = new;
	}
	else
		a->lst_lab = new;
}

void			lst_lab_del_all(t_asm *a)
{
	t_lab *curr_lab;
	t_lab *next_lab;

	curr_lab = a->lst_lab;
	while (curr_lab != NULL)
	{
		next_lab = curr_lab->next;
		free(curr_lab->name);
		free(curr_lab);
		curr_lab = next_lab;
	}
	a->lst_lab = NULL;
}
