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

//faire fonction pour swap toutes les infos des structs contenant des infos

#include "../includes/ft_nm.h"

struct section_64		*find_section_in_seg_64(struct segment_command_64
		*segment, uint32_t sum_sects, uint32_t n_sect)
{
	struct section_64			*section;
	int							index_section;

	section = (struct section_64*)((void*)segment +
			sizeof(struct segment_command_64));
	index_section = segment->nsects - (sum_sects - n_sect) - 1;
	return (&section[index_section]);
}

struct section_64		*find_section_64(uint8_t n_sect, t_manager *manager)
{
	int							i;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	uint32_t					sum_sects;

	i = 0;
	sum_sects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sum_sects += seg->nsects;
			if (n_sect <= sum_sects)
				return (find_section_in_seg_64(seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (NULL);
}

int						fill_symbol_64(t_symbol *symbol, t_manager *manager,
		struct nlist_64 *el)
{
	struct section_64			*section;
	char						*stringtable;

	stringtable = manager->file + manager->symtab->stroff;
	ft_bzero(symbol, sizeof(t_symbol));
	if (el->n_sect != 0)
	{
		if ((section = find_section_64(el->n_sect, manager)) == NULL)
			return (ERROR);
		symbol->sym_type = section->sectname[2];
		if (!ft_strchr(SECT, symbol->sym_type))
			symbol->sym_type = 's';
	}
	else
		study_type(symbol, el->n_type, manager->swap);
	if (el->n_type & N_EXT && symbol->sym_type >= 97)
		symbol->sym_type -= 32;

	symbol->sym_name = stringtable + el->n_un.n_strx;
	symbol->value = el->n_value;
	if (record_symbol(manager, symbol) == ERROR)
		return (ERROR);
	return (TRUE);
}

int						read_symtab_64(t_manager *manager)
{
	int					i;
	struct nlist_64		*el;
	t_symbol			symbol;
	uint32_t			symmof;

	if (manager->swap)
		swap(&symmof, &manager->symtab->symoff, sizeof(uint32_t));
	else
		symmof = manager->symtab->symoff;
	el = (struct nlist_64 *)(manager->file + symmof);
	i = 0;
	while (i < manager->symtab->nsyms) // a swap
	{
		if (!(el[i].n_type & N_STAB))
			fill_symbol_64(&symbol, manager, &el[i]);
		i++;
	}
	print_symbols_64(manager);
	return (TRUE);
}
