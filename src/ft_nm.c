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

int 		record_section(uint8_t n_sect, t_manager *manager,
		struct segment_command_64 *segment, uint32_t sum_nsects)
{
	struct section_64	*section;

	section = (struct section_64*)((void*)manager + segment->fileoff);
	while (sum_nsects != n_sect)
	{
		sum_nsects++;
		section = (void*)section + section->size;
	}

}

int			get_section(uint8_t n_sect, t_manager *manager)
{
	struct load_command			*lc;
	int 						i;
	struct segment_command_64	*segment;
	uint32_t					sum_nsects;

	i = 0;
	sum_nsects = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command_64*)lc;
			if ((sum_nsects + segment->nsects) >= n_sect)
				return (record_section(n_sect, manager, segment, sum_nsects));
			sum_nsects += segment->nsects;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (FALSE);
}

int 		get_symbol(t_symbol *symbol, uint8_t n_type, uint8_t n_sect, t_manager *manager)
{
	if ((n_type & N_TYPE) == N_UNDF)
		*symbol->sym_name = 'U';
	if ((n_type & N_TYPE) == N_SECT)
		get_section(n_sect, manager);
	return (TRUE);
}

int 		read_symtab(struct symtab_command *sym, t_manager *manager)
{
	int 	i;
	struct nlist_64 *el;
	char			*stringtable;
	t_symbol		symbol;

	el = (struct nlist_64 *)(manager->file + sym->symoff);
	stringtable = manager->file + sym->stroff;
	i = 0;

	while (i < sym->nsyms)
	{
		ft_bzero(&symbol, sizeof(t_symbol));
		symbol.sym_name = stringtable + el[i].n_un.n_strx;
		get_symbol(&symbol, el[i].n_type , el[i].n_sect, manager);
		ft_printf("type = %#x, %s\n", el[i].n_type & N_TYPE, stringtable + el[i].n_un.n_strx);
		i++;
	}
	return (TRUE);
}

int			handle_64(t_manager *manager)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int 					i;

	i = 0;
	header = (struct mach_header_64*)manager->file;
	lc = (struct load_command*)((void*)manager->file + sizeof(struct mach_header_64));
	manager->ncmds = header->ncmds;
	while (i < header->ncmds)
	{
//		enregistré dans manager le offset pour le header et ncmds pour ne pas devoir jouer avec les types
		if (lc->cmd == LC_SYMTAB)
		{
			read_symtab((struct symtab_command*)lc, manager);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (TRUE);
}

int 		nm(t_manager *manager)
{
	uint32_t	magic;

	magic = *(uint32_t*)manager->file;
	if (magic == MH_MAGIC_64)
	{
		manager->header_size = sizeof(struct mach_header_64);
		handle_64(manager);
	}
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


