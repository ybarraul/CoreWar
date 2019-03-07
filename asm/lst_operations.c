/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_operations.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 13:53:36 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:18:17 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static t_ope	*lst_ope_new(t_asm *a, t_ope *ope)
{
	t_ope *new;

	new = malloc(sizeof(t_ope));
	if (new == NULL)
	{
		perror("Malloc on new label failed");
		free_all(a);
	}
	ft_memcpy(new, ope, sizeof(t_ope));
	new->next = NULL;
	return (new);
}

void			lst_ope_push(t_asm *a, t_ope *ope)
{
	t_ope *crawler;
	t_ope *new;

	new = lst_ope_new(a, ope);
	if (a->lst_ope != NULL)
	{
		crawler = a->lst_ope;
		while (crawler->next != NULL)
			crawler = crawler->next;
		crawler->next = new;
	}
	else
		a->lst_ope = new;
}

void			lst_ope_del_all(t_asm *a)
{
	t_ope *curr_ope;
	t_ope *next_ope;

	curr_ope = a->lst_ope;
	while (curr_ope != NULL)
	{
		next_ope = curr_ope->next;
		free(curr_ope->p_un.label);
		free(curr_ope->p_de.label);
		free(curr_ope->p_tr.label);
		free(curr_ope);
		curr_ope = next_ope;
	}
	a->lst_ope = NULL;
}
