/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nm_64.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 15:10:29 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 15:10:29 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/nm_otool.h"

struct section_64		*find_sec_in_seg_64(t_manager *manager,
		struct segment_command_64 *segment, uint32_t sum_sects, uint32_t n_sect)
{
	struct section_64			*section;
	uint32_t					index_section;
	uint32_t					nsects;

	nsects = segment->nsects;
	if (manager->swap)
		ft_memrev(&nsects, sizeof(char), sizeof(uint32_t));
	section = (struct section_64*)((void*)segment +
			sizeof(struct segment_command_64));
	index_section = nsects - (sum_sects - n_sect) - 1;
	return (&section[index_section]);
}

struct section_64		*find_section_64(uint8_t n_sect, t_manager *manager)
{
	uint32_t					i;
	struct load_command			*lc;
	struct load_command			lc_temp;
	struct segment_command_64	*seg;
	uint32_t					sum_sects;

	i = 0;
	sum_sects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		ft_memcpy(&lc_temp, lc, sizeof(struct load_command));
		if (manager->swap)
			swap_lc(&lc_temp, lc);
		if (lc_temp.cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sum_sects += add_nsect(&seg->nsects, manager->swap);
			if (n_sect <= sum_sects)
				return (find_sec_in_seg_64(manager, seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (NULL);
}

int						fill_symbol_64(t_symbol *symbol, t_manager *manager,
		struct nlist_64 *el)
{
	struct section_64			*section;
	char						*stringtable;

	stringtable = manager->file + manager->symtab.stroff;
	symbol->sym_type = 0;
	symbol->is64 = 1;
	symbol->value64 = el->n_value;
	if ((el->n_type & N_TYPE) == N_SECT)
	{
		if ((section = find_section_64(el->n_sect, manager)) == NULL)
			return (ERROR);
		check_section_name(symbol, section->sectname);
	}
	else
		study_type(symbol, el->n_type);
	if (el->n_type & N_EXT && symbol->sym_type >= 97)
		symbol->sym_type -= 32;
	symbol->sym_name = stringtable + el->n_un.n_strx;
	if (record_symbol(manager, symbol) == ERROR)
		return (ERROR);
	return (TRUE);
}

int						read_symtab_64(t_manager *manager)
{
	uint32_t			i;
	struct nlist_64		*el;
	struct nlist_64		el_temp;
	t_symbol			symbol;

	el = (struct nlist_64 *)(manager->file + manager->symtab.symoff);
	i = 0;
	while (i < manager->symtab.nsyms)
	{
		ft_bzero(&symbol, sizeof(t_symbol));
		ft_memcpy(&el_temp, &el[i], sizeof(struct nlist_64));
		if (manager->swap)
			swap_nlist64(&el_temp, &el[i]);
		if (!(el_temp.n_type & N_STAB))
			if (fill_symbol_64(&symbol, manager, &el_temp) == ERROR)
				return (FALSE);
		i++;
	}
	print_symbols_64(manager);
	free_symbols(manager->symbol_list);
	manager->symbol_list = NULL;
	return (TRUE);
}
