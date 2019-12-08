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

#include "../includes/ft_nm.h"

void					study_type(t_symbol *symbol, uint8_t n_type)
{
	uint8_t				type;

	type = n_type & N_TYPE;
	if (type == N_UNDF || type == N_PBUD)
		symbol->sym_type += 'U';
	else if (type == N_ABS)
		symbol->sym_type += 'A';
	else if (type == N_INDR)
		symbol->sym_type += 'S';
}

int							find_lc_symtab(t_manager *manager)
{
	int						i;
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

int			handle_64(t_manager *manager)
{
	struct mach_header_64	*header64;

	header64 = (struct mach_header_64*)manager->file;
	if (*(uint32_t*)manager->file ==MH_CIGAM_64)
		manager->swap = 1;
	manager->_64 = 1; // surement inutile
	manager->header_size = sizeof(struct mach_header_64);
	manager->ncmds = header64->ncmds;
	if (find_lc_symtab(manager) && read_symtab_64(manager))
		return (TRUE);
	return (FALSE);
}

int			handle_32(t_manager *manager)
{
	struct mach_header	*header;

	header = (struct mach_header*)manager->file;
	if (*(uint32_t*)manager->file ==MH_CIGAM)
		manager->swap = 1;
	manager->header_size = sizeof(struct mach_header);
	manager->ncmds = header->ncmds;
	if (find_lc_symtab(manager) && read_symtab_32(manager))
		return (TRUE);
	return (FALSE);
}


int							nm(t_manager *manager)
{
	uint32_t				magic;

	magic = *(uint32_t*)manager->file;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (handle_64(manager));
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (handle_32(manager));
//	else if (ft_strncmp(ARMAG, manager->file, SARMAG) == 0)
//		study_arch(manager);
//	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
//	{
//		study_fat_32(manager);
//	}
//	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
//	{
//		study_fat_64(manager);
//	}
	return (TRUE);
}

int							main(int ac, char **av)
{
	int						i;
	int						ret;

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
