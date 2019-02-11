/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 01:26:11 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 21:40:16 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Fonction : is_size
**-----------------------
**	retourne 1 si c correspond a une taille de donnée
*/

int			is_size(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 't')
		return (1);
	return (0);
}

/*
** Fonction: is_flag
**----------------------
** retourne 1 si c correspond a un flag de printf
** flags >> 25 == '-'
*/

int			is_flag(char c, uint64_t flags)
{
	if (c == '#' || (c == '0' && !((flags >> 25) & 1)) || c ==\
		'-' || c == '+' || c == ' ' || c == '.')
		return (1);
	return (0);
}

/*
** Fonction: is_type
**----------------------
** retourne 1 si c correspond a un type de donnée
*/

int			is_type(char c)
{
	if (c == '%' || (ft_isalpha(c) && !is_size(c)))
		return (1);
	return (0);
}

/*
** Fonction:biggest
**-----------------------
** Fonction utilisé pour corriger les erreurs de taille de donnée donne par
** l'utilisateur
** s'il y a le/s taille/s h(flag >> 13) ou hh(flag >> 14) et d'autre tailles
** suprérieures, la fonction supprime les type h et hh.
** la taille de base n'a pas de flag
** les autres taille, dans notre cas, font toutes 64 bits (sizeof4evar)
*/

void		biggest(uint64_t *flags)
{
	if (((*flags >> 13) & 1 || (*flags >> 14) & 1) && (*flags >> 15) & 0x1F)
		*flags &= 0xFFFFFFFFFFFF9FFF;
}

/*
** Fonction:is_parse
**-------------------
** Pour trouver la suite de format dans ft_printf
*/

int			is_parse(char c)
{
	if (!is_type(c) && (is_size(c) || (c >= '0' && c <= '9') ||\
	c == '#' || c == '-' || c == '+' || c == ' ' || c == '.'))
		return (1);
	return (0);
}
