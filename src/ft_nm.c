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

int 		read_symtab(struct symtab_command *lc, t_manager *manager)
{
	int 	i;
	struct nlist_64 *el;
	char			*stringtable;

	el = (struct nlist_64 *)(manager->file + lc->symoff);
	stringtable = manager->file + lc->stroff;
	i = 0;
	while (i < lc->nsyms)
	{
		ft_printf("%s\n", stringtable + el[i].n_un.n_strx);
		i++;
	}
	return (TRUE);
}

int			handle_64(t_manager *manager)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int 					i;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64*)manager->file;
	lc = (struct load_command*)((void*)manager->file + sizeof(struct mach_header_64));
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
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
	printf("magic = %#x\n", *(int*)ft_memrev(&magic, 1, 4));
	if (magic == MH_MAGIC_64)
	{
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


