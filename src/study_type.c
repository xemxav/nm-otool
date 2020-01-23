/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   study_type.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 13:22:18 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 13:22:18 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void					study_type(t_symbol *symbol, uint8_t n_type)
{
	uint8_t				type;

	type = n_type & N_TYPE;
	if (type == N_UNDF && symbol->value64 == 0 && symbol->value32 == 0)
		symbol->sym_type += 'U';
	if (type == N_UNDF && (symbol->value64 != 0 || symbol->value32 != 0))
		symbol->sym_type += 'C';
	else if (type == N_ABS)
		symbol->sym_type += 'A';
	else if (type == N_INDR)
		symbol->sym_type += 'I';
}

void		check_section_name(t_symbol *symbol, char *sectname)
{
	if (ft_strcmp(sectname, TEXT) == 0)
		symbol->sym_type = 't';
	else if (ft_strcmp(sectname, DATA) == 0)
		symbol->sym_type = 'd';
	else if (ft_strcmp(sectname, BSS) == 0)
		symbol->sym_type = 'b';
	else
		symbol->sym_type = 's';
}