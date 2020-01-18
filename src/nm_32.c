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

//faire fonction pour swap toutes les infos des structs contenant des infos



struct section		*find_section_in_seg(t_manager *manager,
		struct segment_command *segment, uint32_t sum_sects, uint32_t n_sect)
{
	struct section				*section;
	int							index_section;
	struct segment_command		seg_temp;

	ft_memcpy(&seg_temp, segment, sizeof(struct segment_command));
	if (manager->swap)
		swap(&seg_temp, segment, sizeof(struct segment_command));
	section = (struct section*)((void*)segment +
			sizeof(struct segment_command));
	index_section = seg_temp.nsects - (sum_sects - n_sect) - 1;
	return (&section[index_section]);
}

struct section		*find_section_32(uint8_t n_sect, t_manager *manager)
{
	int							i;
	struct load_command			*lc;
	struct load_command			lc_temp;
	struct segment_command		*seg;
	uint32_t					sum_sects;

	i = 0;
	sum_sects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		ft_memcpy(&lc_temp, lc, sizeof(struct load_command));
		if (manager->swap)
			swap_lc(&lc_temp, lc);
		if (lc_temp.cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			sum_sects += add_nsect(&seg->nsects, manager->swap);
			if (n_sect <= sum_sects)
				return (find_section_in_seg(manager, seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (NULL);
}

int						fill_symbol_32(t_symbol *symbol, t_manager *manager,
										  struct nlist *el)
{
	struct section			*section;
	char					*stringtable;

	stringtable = manager->file + manager->symtab.stroff;
	if (el->n_sect != 0)
	{
		if ((section = find_section_32(el->n_sect, manager)) == NULL)
			return (ERROR);
		symbol->sym_type = section->sectname[2];
		if (!ft_strchr(SECT, symbol->sym_type))
			symbol->sym_type = 's';
	}
	else
		study_type(symbol, el->n_type);
	if (el->n_type & N_EXT && symbol->sym_type >= 97)
		symbol->sym_type -= 32;
	symbol->sym_name = stringtable + el->n_un.n_strx;
	symbol->value = el->n_value;
	if (record_symbol(manager, symbol) == ERROR)
		return (ERROR);
	return (TRUE);
}

int						read_symtab_32(t_manager *manager)
{
	int						i;
	struct nlist			*el;
	t_symbol				symbol;
	struct nlist			el_temp;

	el = (struct nlist*)(manager->file + manager->symtab.symoff);
	i = 0;
	while (i < manager->symtab.nsyms)
	{
		ft_bzero(&symbol, sizeof(t_symbol));
		ft_memcpy(&el_temp, &el[i], sizeof(struct nlist));
		if (manager->swap)
			swap_nlist(&el_temp, el);
		if (!(el_temp.n_type & N_STAB))
			fill_symbol_32(&symbol, manager, &el_temp);
		i++;
	}
	print_symbols_32(manager);
	return (TRUE);
}