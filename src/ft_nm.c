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

int							nm(t_manager *manager)
{
	uint32_t				magic;
	struct mach_header_64	*header64;

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
