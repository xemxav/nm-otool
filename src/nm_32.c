/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nm_32.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/07 16:59:17 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2019/12/07 16:59:17 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

struct section		*find_section_in_seg(struct segment_command
		*segment, uint32_t sum_sects, uint32_t n_sect)
{
	struct section				*section;
	int							index_section;

	section = (struct section*)((void*)segment +
								   sizeof(struct segment_command));
	index_section = segment->nsects - (sum_sects - n_sect) - 1;
	return (&section[index_section]);
}

struct section		*find_section_32(uint8_t n_sect, t_manager *manager)
{
	int							i;
	struct load_command			*lc;
	struct segment_command		*seg;
	uint32_t					sum_sects;

	i = 0;
	sum_sects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			sum_sects += seg->nsects;
			if (n_sect <= sum_sects)
				return (find_section_in_seg(seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (NULL);
}

int						fill_symbol_32(t_symbol *symbol, t_manager *manager,
										  struct nlist *el)
{
	struct section			*section;
	char					*stringtable;

	stringtable = manager->file + manager->symtab->stroff;
	ft_bzero(symbol, sizeof(t_symbol));
	if (el->n_sect != 0)
	{
		if ((section = find_section_32(el->n_sect, manager)) == NULL)
			return (ERROR);
		symbol->sym_type = section->sectname[2];
	}
	else
		study_type(symbol, el->n_type);
	if (el->n_type & N_EXT && symbol->sym_type >= 97)
		symbol->sym_type -= 32;
	symbol->sym_name = stringtable + el->n_un.n_strx;
	symbol->value = el->n_value;
	if (record_symbol_64(manager, symbol) == ERROR)
		return (ERROR);
	return (TRUE);
}

int						read_symtab_32(t_manager *manager)
{
	int					i;
	struct nlist		*el;
	t_symbol			symbol;

	el = (struct nlist*)(manager->file + manager->symtab->symoff);
	i = 0;
	while (i < manager->symtab->nsyms)
	{
		if (!(el[i].n_type & N_STAB))
			fill_symbol_32(&symbol, manager, &el[i]);
		i++;
	}
	print_symbols_64(manager);
	return (TRUE);
}