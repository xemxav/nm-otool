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

#include "../../includes/nm_otool.h"

void			study_type(t_symbol *symbol, uint8_t n_type)
{
	uint8_t		type;
	int			value;

	value = 0;
	if (symbol->is64 && symbol->value64 > 0)
		value = 1;
	if (!symbol->is64 && symbol->value32 > 0)
		value = 1;
	type = n_type & N_TYPE;
	if (type == N_UNDF && value == 0)
		symbol->sym_type += 'U';
	if (type == N_UNDF && value != 0)
		symbol->sym_type += 'C';
	else if (type == N_ABS)
		symbol->sym_type += 'A';
	else if (type == N_INDR)
		symbol->sym_type += 'I';
}

void			check_section_name(t_symbol *symbol, char *sectname)
{
	if (ft_strcmp(sectname, SECT_TEXT) == 0)
		symbol->sym_type = 't';
	else if (ft_strcmp(sectname, SECT_DATA) == 0)
		symbol->sym_type = 'd';
	else if (ft_strcmp(sectname, SECT_BSS) == 0)
		symbol->sym_type = 'b';
	else
		symbol->sym_type = 's';
}
