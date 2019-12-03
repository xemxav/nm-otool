/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nm.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:01:13 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:01:13 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include "../includes/ft_nm.h"

//int 		record_section(uint8_t n_sect, t_manager *manager,
//		struct segment_command_64 *segment, uint32_t sum_nsects)
//{
//	struct section_64	*section;
//
//	section = (struct section_64*)((void*)manager + segment->fileoff);
//	while (sum_nsects != n_sect)
//	{
//		sum_nsects++;
//		section = (void*)section + section->size;
//	}
//
//}

//int			get_section(uint8_t n_sect, t_manager *manager)
//{
//	struct load_command			*lc;
//	int 						i;
//	struct segment_command_64	*segment;
//	uint32_t					sum_nsects;
//
//	i = 0;
//	sum_nsects = 0;
//	lc = (struct load_command*)((void*)manager->file + manager->header_size);
//	while (i < manager->ncmds)
//	{
//		if (lc->cmd == LC_SEGMENT)
//		{
//			segment = (struct segment_command_64*)lc;
//			if ((sum_nsects + segment->nsects) >= n_sect)
//				return (record_section(n_sect, manager, segment, sum_nsects));
//			sum_nsects += segment->nsects;
//		}
//		lc = (void*)lc + lc->cmdsize;
//		i++;
//	}
//	return (FALSE);
//}
//
//int 		get_symbol(t_symbol *symbol, uint8_t n_type, uint8_t n_sect, t_manager *manager)
//{
//	if ((n_type & N_TYPE) == N_UNDF)
//		*symbol->sym_name = 'U';
//	if ((n_type & N_TYPE) == N_SECT)
//		get_section(n_sect, manager);
//	return (TRUE);
//}
//

struct section_64	*find_section_in_seg_64(struct segment_command_64 *segment, uint8_t sum_sects, uint8_t n_sect)
{
	struct section_64			*section;
	int 						i;
	int 						index_section;

	i = 0;
	index_section = sum_sects - segment->nsects + 1;
	section = (struct section_64*)((void*)segment + sizeof(struct segment_command_64));
	while (i < segment->nsects && index_section != n_sect)
	{
//		ft_printf("sectnane = %s\n",section[i].sectname);
		index_section++;
		i++;
	}
	ft_printf("secname = %s\n", section[i].sectname);
	return (&section[i]);
}

struct section_64 		*find_section_64(uint8_t n_sect, t_manager *manager)
{
	int 					i;
	struct load_command		*lc;
	struct segment_command_64 *seg;
	uint32_t				sum_sects;

	i = 0;
	sum_sects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sum_sects += seg->nsects;
//			ft_printf("segname = %s\n", seg->segname);
			if (n_sect <= sum_sects)
				return (find_section_in_seg_64(seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (NULL);
}

int 		read_symtab_64(t_manager *manager)
{
	int 	i;
	struct nlist_64 *el;
	char			*stringtable;
//	t_symbol		symbol;

	el = (struct nlist_64 *)(manager->file + manager->symtab->symoff);
	stringtable = manager->file + manager->symtab->stroff;
	i = 0;
	while (i < manager->symtab->nsyms)
	{
//		if (!(el[i].n_type & N_STAB))
//		{
//			if ((el[i].n_type & N_TYPE) == N_UNDF)
//				symbol.sym_type = 'u';
//
//			symbol.ext = el[i].n_type & N_EXT;
//			symbol.sym_name = stringtable + el[i].n_un.n_strx;
//			symbol.value = el[i].n_value;
//		}
//		if (el[i].n_type & N_EXT)
//			symbol.sym_type = 32
		if (el[i].n_sect != 0)
			find_section_64(el[i].n_sect, manager);
		ft_printf("value = %#.16x , n_sect = %d, type = %.8b, n_strx = %d,  %s\n", el[i].n_value,el[i].n_sect, el[i].n_type,el[i].n_un.n_strx, stringtable + el[i].n_un.n_strx);
		i++;
	}
	return (TRUE);
}

int			find_lc_symtab(t_manager *manager)
{
	int 					i;
	struct load_command		*lc;

	i = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			manager->symtab = (struct symtab_command*)lc;
			return (TRUE);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (FALSE);
}

int 		nm(t_manager *manager)
{
	uint32_t	magic;
	struct mach_header_64* header64;

	magic = *(uint32_t*)manager->file;
	if (magic == MH_MAGIC_64)
	{
		header64 = (struct mach_header_64*)manager->file;
		manager->_64 = 1;
		manager->header_size = sizeof(struct mach_header_64);
		manager->ncmds = header64->ncmds;
	}
	find_lc_symtab(manager);
	if (manager->_64)
		read_symtab_64(manager);
	return (TRUE);
}

int			main(int ac, char **av)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (ac == 1)
		ret = open_file("a.out", "ft_nm", &nm);
	else
	{
		while (i < ac && ret != ERROR)
		{
			ret = open_file(av[i], "ft_nm", &nm);
			i++;
		}
	}
	return (ret);
}


