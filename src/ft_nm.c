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

struct section_64	*find_section_in_seg_64(struct segment_command_64 *segment, uint32_t sum_sects, uint32_t n_sect)
{
	struct section_64			*section;
	int 						index_section;

	section = (struct section_64*)((void*)segment + sizeof(struct segment_command_64));
	index_section = segment->nsects - (sum_sects - n_sect) - 1;
	return (&section[index_section]);
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
			if (n_sect <= sum_sects)
				return (find_section_in_seg_64(seg, sum_sects, n_sect));
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (NULL);
}

void		study_type(t_symbol *symbol, uint8_t n_type)
{
	uint8_t		type;

	type = n_type & N_TYPE;
	if (type == N_UNDF || type == N_PBUD)
		symbol->sym_type += 'U';
	else if (type == N_ABS)
		symbol->sym_type += 'A';
	else if (type == N_INDR)
		symbol->sym_type += 'S';
}

void		print_symbols_64(t_manager *manager)
{
	t_symbol	*symbol;

	symbol = manager->symbol_list;
	while (symbol != NULL)
	{
		if (symbol->sym_type != 'u' &&  symbol->sym_type != 'U')
			ft_printf("%.16llx", symbol->value);
		else
			ft_printf("                ");
		ft_printf(" %c %s\n", symbol->sym_type, symbol->sym_name);
		symbol = symbol->next;
	}
}

void		insert_symbol(t_manager *manager, t_symbol *new)
{
	t_symbol	*first;
	t_symbol	*second;

	first = NULL;
	second = manager->symbol_list;
	while (second != NULL && ft_strcmp(second->sym_name, new->sym_name) < 0)
	{
		first = second;
		second = second->next;
	}
	new->next = second;
	if (first)
		first->next = new;
	else
		manager->symbol_list = new;
}

int			record_symbol(t_manager *manager, t_symbol *symbol)
{
	t_symbol	*new;


	if ((new = (t_symbol*)malloc(sizeof(t_symbol))) == NULL)
		return (ERROR);
	ft_memcpy(new, symbol, sizeof(t_symbol));
	if (manager->symbol_list == NULL)
		manager->symbol_list = new;
	else
	{
		insert_symbol(manager, new);
	}
	return (TRUE);
}

int 		read_symtab_64(t_manager *manager)
{
	int 	i;
	struct nlist_64 *el;
	char			*stringtable;
	t_symbol		symbol;
	struct section_64			*section;

	el = (struct nlist_64 *)(manager->file + manager->symtab->symoff);
	stringtable = manager->file + manager->symtab->stroff;
	i = 0;
	while (i < manager->symtab->nsyms)
	{
		if (!(el[i].n_type & N_STAB))
		{
			ft_bzero(&symbol, sizeof(t_symbol));
			if (el[i].n_sect != 0)
			{
				section = find_section_64(el[i].n_sect, manager);
				symbol.sym_type += section->sectname[2];
			}
			else
				study_type(&symbol, el[i].n_type);
			if (el[i].n_type & N_EXT && symbol.sym_type >= 97)
				symbol.sym_type -= 32;
			symbol.sym_name = stringtable + el[i].n_un.n_strx;
			symbol.value = el[i].n_value;
			record_symbol(manager, &symbol);
		}
		i++;
	}
	print_symbols_64(manager);
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


