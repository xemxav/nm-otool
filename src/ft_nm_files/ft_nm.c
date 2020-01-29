/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nm.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:08:48 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 17:08:48 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/nm_otool.h"

int							find_lc_symtab(t_manager *manager)
{
	uint32_t				i;
	struct load_command		*lc;
	struct load_command		lc_temp;

	i = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		ft_memcpy(&lc_temp, lc, sizeof(struct load_command));
		if (manager->swap)
			swap_lc(&lc_temp, lc);
		if (lc_temp.cmd == LC_SYMTAB)
		{
			ft_memcpy(&manager->symtab, lc, sizeof(struct symtab_command));
			if (manager->swap)
				swap_symtab(&manager->symtab, (struct symtab_command*)lc);
			return (TRUE);
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (FALSE);
}

static int					handle_64(t_manager *manager)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64*)manager->file;
	manager->ncmds = header->ncmds;
	if (*(uint32_t*)manager->file == MH_CIGAM_64)
	{
		manager->swap = 1;
		swap(&manager->ncmds, &header->ncmds, sizeof(uint32_t));
	}
	manager->header_size = sizeof(struct mach_header_64);
	if (find_lc_symtab(manager) && read_symtab_64(manager))
	{
		manager->swap = 0;
		return (TRUE);
	}
	return (FALSE);
}

static int					handle_32(t_manager *manager)
{
	struct mach_header		*header;

	header = (struct mach_header*)manager->file;
	if (*(uint32_t*)manager->file == MH_CIGAM)
	{
		manager->swap = 1;
		swap(&manager->ncmds, &header->ncmds, sizeof(uint32_t));
	}
	else
		manager->ncmds = header->ncmds;
	manager->header_size = sizeof(struct mach_header);
	if (find_lc_symtab(manager) && read_symtab_32(manager))
	{
		manager->swap = 0;
		return (TRUE);
	}
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
	else if (ft_strncmp(ARMAG, manager->file, SARMAG) == 0)
		return (study_lib(manager));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (study_fat_32(manager));
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (study_fat_64(manager));
	return (FALSE);
}

int							main(int ac, char **av)
{
	int						i;
	int						ret;
	int						several;

	i = 1;
	ret = 0;
	if (ac == 1)
		ret = open_file("a.out", "ft_nm_files", &nm, 0);
	else
	{
		several = (ac > 2) ? 1 : 0;
		while (i < ac && ret != ERROR)
		{
			ret = open_file(av[i], "ft_nm_files", &nm, several);
			i++;
		}
	}
	return (ret);
}
