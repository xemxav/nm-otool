/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_otool_files.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:10:20 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 15:10:20 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static int						handle_64(t_manager *manager)
{
	struct mach_header_64		*header;

	header = (struct mach_header_64*)manager->file;
	manager->ncmds = header->ncmds;
	if (*(uint32_t*)manager->file == MH_CIGAM_64)
	{
		manager->swap = 1;
		swap(&manager->ncmds, &header->ncmds, sizeof(uint32_t));
	}
	manager->header_size = sizeof(struct mach_header_64);
	if (find_text_64(manager) <= 0)
		return (ERROR);
	return (TRUE);
}

static int						handle_32(t_manager *manager)
{
	struct mach_header			*header;

	if (manager->file_tmp == NULL)
		manager->file_tmp = manager->file;
	header = (struct mach_header*)manager->file;
	if (*(uint32_t*)manager->file == MH_CIGAM)
	{
		manager->swap = 1;
		swap(&manager->ncmds, &header->ncmds, sizeof(uint32_t));
	}
	else
		manager->ncmds = header->ncmds;
	manager->header_size = sizeof(struct mach_header);
	if (find_text_32(manager) <= 0)
		return (ERROR);
	return (TRUE);
}

int							otool(t_manager *manager)
{
	uint32_t				magic;

	magic = *(uint32_t*)manager->file;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (handle_64(manager));
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (handle_32(manager));
//	else if (ft_strncmp(ARMAG, manager->file, SARMAG) == 0)
//		return (study_lib(manager));
//	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
//		return (study_fat_32(manager));
//	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
//		return (study_fat_64(manager));
//	return (FALSE);
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
		ret = open_file("a.out", "ft_otool_files", &otool, 0);
	else
	{
		several = (ac > 2) ? 1 : 0;
		while (i < ac && ret != ERROR)
		{
			ret = open_file(av[i], "ft_otool_files", &otool, several);
			i++;
		}
	}
	return (ret);
}
