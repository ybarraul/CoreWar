/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_find_infos.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 18:26:33 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 21:42:26 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Fonction : fill_data_type
**-----------------------------
** rempli flags avec le bon type de donné
*/

static void		ft_fill_data_type(uint64_t *flags, char type)
{
	if (type == 's')
		*flags |= 0x1;
	else if (type == 'S')
		*flags |= 0x2;
	else if (type == 'p')
		*flags |= 0x4;
	else if (type == 'd' || type == 'i')
		*flags |= 0x8;
	else if (type == 'D')
		*flags |= 0x10;
	else if (type == 'o')
		*flags |= 0x20;
	else if (type == 'O')
		*flags |= 0x40;
	else if (type == 'u')
		*flags |= 0x80;
	else if (type == 'U')
		*flags |= 0x100;
	else if (type == 'x')
		*flags |= 0x200;
	else if (type == 'X')
		*flags |= 0x400;
	else if (type == 'c' || type == 'C')
		*flags |= 0x800;
}

/*
** Fonction: fill_size_type
**-----------------------------
** Rempli flags avec le/s taille/s donnée/s
*/

static void		ft_fill_size_type(uint64_t *flags, char **arg_type)
{
	if (**arg_type == 'h' && *(*(arg_type) + 1) != 'h')
		*flags |= 0x2000;
	else if (**arg_type == 'h' && *(*(arg_type) + 1) == 'h')
	{
		*flags |= 0x4000;
		*arg_type = *(arg_type) + 1;
	}
	else if (**arg_type == 'l' && *(*(arg_type) + 1) != 'l')
		*flags |= 0x8000;
	else if (**arg_type == 'l' && *(*(arg_type) + 1) == 'l')
	{
		*flags |= 0x10000;
		*arg_type = *(arg_type) + 1;
	}
	else if (**arg_type == 'j')
		*flags |= 0x20000;
	else if (**arg_type == 'z')
		*flags |= 0x40000;
	else if (**arg_type == 't')
		*flags |= 0x80000;
}

/*
** Fonction: fill_spec
**------------------------
** Rempli flags avec les flag speciaux
*/

static void		ft_fill_spec(uint64_t *flags, char spec)
{
	if (spec == '#')
		*flags |= 0x100000;
	else if (spec == '0')
		*flags |= 0x200000;
	else if (spec == '-')
		*flags |= 0x400000;
	else if (spec == '+')
		*flags |= 0x800000;
	else if (spec == ' ')
		*flags |= 0x1000000;
	else if (spec == '.')
		*flags |= 0x2000000;
}

/*
** Fonction: fill_width-prec
**-----------------------------
** Rempli flags avec la précision et la largeur
** Pour le moment les deux sont coder sur 8bits (255 max)
*/

static void		ft_fill_width_prec(uint64_t *flags, char **str)
{
	int		i;

	if ((i = ft_atoi(*str)) > 255)
	{
		write(1, "prec/width trop grand, remis a max 255\n", 39);
		i = 255;
	}
	if ((*flags >> 25) & 1)
		*flags = (*flags & 0xFFFFF807FFFFFFFF) | ((uint64_t)i << 35);
	else
		*flags = (*flags & 0xFFFFFFF807FFFFFF) | ((uint64_t)i << 27);
	while (*(*str + 1) >= '0' && *(*str + 1) <= '9')
		*str += 1;
}

/*
** Fonction: parser
**----------------------------
** Parse la chaine de charactere str et rempli flags avec les données trouver
** quitte la boucle une fois le type de donnée trouver
** verifie qu'il n'y a pas le flag 0 si le flag - est present, supprime 0
** verifie qu'il n'y a pas le flag 0 si precision avec type integer, suppr 0
** return null si type de donnée trouver, str pour le premier char trouver
** qui n'est pas un type de donnée pour les undefined behavior
** retourne str si aucun type trouver
*/

char			*ft_find_data_type(uint64_t *flags, char *str)
{
	while (*str)
	{
		str++;
		if (is_flag(*str, *flags))
			ft_fill_spec(flags, *str);
		if (*str >= '0' && *str <= '9')
			ft_fill_width_prec(flags, &str);
		if (is_size(*str))
			ft_fill_size_type(flags, &str);
		else if (is_type(*str))
		{
			*str == '%' ? *flags += 0x1000 : ft_fill_data_type(flags, *str);
			break ;
		}
	}
	if (((*flags >> 21) & 1) && ((*flags >> 22) & 1))
		*flags &= 0xFFFFFFFFFDFFFFF;
	if ((*flags >> 21) & 1 && (*flags >> 25) & 1 && (*flags & 0x7F8))
		*flags &= 0xFFFFFFFFFDFFFFF;
	biggest(flags);
	return (((*flags & 0x1FFF) == 0) ? str : NULL);
}
