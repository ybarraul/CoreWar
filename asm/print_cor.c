/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_cor.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 17:51:49 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:29:44 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	print_param(t_param *p, int fd_dest, int cur_pos, char s[4])
{
	if (p->type != 0)
	{
		if (p->size == 1)
			s[0] = p->val;
		else if (p->size == 2)
		{
			s[0] = p->val >> 8;
			s[1] = p->val;
		}
		else if (p->size == 4)
		{
			s[0] = p->val >> 24;
			s[1] = p->val >> 16;
			s[2] = p->val >> 8;
			s[3] = p->val;
		}
		write(fd_dest, s, p->size);
		cur_pos += p->size;
	}
	return (cur_pos);
}

static int	print_opc(t_ope *lst_ope, int fd_dest, int cur_pos, char s[4])
{
	if (lst_ope->opc)
	{
		s[0] = 0;
		if (lst_ope->p_un.type == T_REG)
			s[0] |= 0b01000000;
		else if (lst_ope->p_un.type == T_DIR)
			s[0] |= 0b10000000;
		else if (lst_ope->p_un.type == T_IND)
			s[0] |= 0b11000000;
		if (lst_ope->p_de.type == T_REG)
			s[0] |= 0b00010000;
		else if (lst_ope->p_de.type == T_DIR)
			s[0] |= 0b00100000;
		else if (lst_ope->p_de.type == T_IND)
			s[0] |= 0b00110000;
		if (lst_ope->p_tr.type == T_REG)
			s[0] |= 0b00000100;
		else if (lst_ope->p_tr.type == T_DIR)
			s[0] |= 0b00001000;
		else if (lst_ope->p_tr.type == T_IND)
			s[0] |= 0b00001100;
		write(fd_dest, s, 1);
		cur_pos++;
	}
	return (cur_pos);
}

static int	print_op(t_ope *lst_ope, int fd_dest, int cur_pos, char s[4])
{
	s[0] = lst_ope->op;
	write(fd_dest, s, 1);
	cur_pos++;
	return (cur_pos);
}

static void	get_correct_label_pos(t_ope *lst_ope, int cur_pos)
{
	if (lst_ope->p_un.label != NULL)
		lst_ope->p_un.val -= cur_pos;
	if (lst_ope->p_de.label != NULL)
		lst_ope->p_de.val -= cur_pos;
	if (lst_ope->p_tr.label != NULL)
		lst_ope->p_tr.val -= cur_pos;
}

void		print_cor(t_asm *a, int fd_dest)
{
	char	s[4];
	t_ope	*curr_op;
	t_ope	*next_op;
	int		cur_pos;

	cur_pos = 0;
	curr_op = a->lst_ope;
	while (curr_op != NULL)
	{
		next_op = curr_op->next;
		get_correct_label_pos(curr_op, cur_pos);
		cur_pos = print_op(curr_op, fd_dest, cur_pos, s);
		cur_pos = print_opc(curr_op, fd_dest, cur_pos, s);
		cur_pos = print_param(&curr_op->p_un, fd_dest, cur_pos, s);
		cur_pos = print_param(&curr_op->p_de, fd_dest, cur_pos, s);
		cur_pos = print_param(&curr_op->p_tr, fd_dest, cur_pos, s);
		curr_op = next_op;
	}
}
