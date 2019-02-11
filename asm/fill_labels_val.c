/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_labels_val.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:33:28 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:01:01 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		find_label(t_asm *a, char *label)
{
	t_lab *lab_crawler;

	lab_crawler = a->lst_lab;
	while (lab_crawler != NULL)
	{
		if (!ft_strcmp(lab_crawler->name, label))
			return (lab_crawler->pos);
		lab_crawler = lab_crawler->next;
	}
	ft_printf("Label |%s| not found\n", label);
	free_all(a);
	return (-1);
}

void			fill_label_val(t_asm *a)
{
	t_ope *ope_crawler;

	ope_crawler = a->lst_ope;
	while (ope_crawler != NULL)
	{
		if (ope_crawler->p_un.label != NULL)
			ope_crawler->p_un.val = find_label(a, ope_crawler->p_un.label);
		if (ope_crawler->p_de.label != NULL)
			ope_crawler->p_de.val = find_label(a, ope_crawler->p_de.label);
		if (ope_crawler->p_tr.label != NULL)
			ope_crawler->p_tr.val = find_label(a, ope_crawler->p_tr.label);
		ope_crawler = ope_crawler->next;
	}
	lst_lab_del_all(a);
	a->lst_lab = NULL;
}
