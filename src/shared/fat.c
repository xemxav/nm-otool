/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fat.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:11:22 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 17:11:22 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/nm_otool.h"

static void					print_file_arch_name(t_manager *manager,
		cpu_type_t *cputype)
{
	char					*a_name;
	cpu_type_t				type;

	swap(&type, cputype, sizeof(cpu_type_t));
	a_name = get_arch_name(type);
	if (manager->otool)
	{
		if (a_name)
			ft_printf("%s (architecture %s):\n", manager->filename, a_name);
		else
			ft_printf("%s:\n", manager->filename);
	}
	else
	{
		if (a_name)
			ft_printf("\n%s (for architecture %s):\n",
					manager->filename, a_name);
		else
			ft_printf("\n%s (for architecture ):\n", manager->filename);
	}
}

static int					all_fat_64(t_manager *manager,
		uint32_t nfat_arch_ind)
{
	uint32_t				offset;
	struct fat_arch_64		*arch;
	uint32_t				i;

	i = 0;
	manager->file_tmp = manager->file;
	manager->lib = 1;
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		manager->file += *(uint32_t*)
				(swap(&offset, &arch[i].offset, sizeof(uint32_t)));
		print_file_arch_name(manager, &arch[i].cputype);
		if (manager->funct(manager) != TRUE)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

static int					all_fat_32(t_manager *manager,
		uint32_t nfat_arch_ind)
{
	uint32_t				offset;
	struct fat_arch			*arch;
	uint32_t				i;

	i = 0;
	manager->file_tmp = manager->file;
	manager->lib = 1;
	arch = (struct fat_arch*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		swap(&offset, &arch[i].offset, sizeof(uint32_t));
		manager->file += offset;
		print_file_arch_name(manager, &arch[i].cputype);
		if (manager->funct(manager) != TRUE)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int							study_fat_64(t_manager *manager)
{
	struct fat_arch_64		*arch;
	struct fat_arch_64		temp;
	uint32_t				nfat_arch;
	uint32_t				i;

	i = 0;
	ft_bzero(&temp, sizeof(struct fat_arch));
	nfat_arch = get_arch_nb(manager);
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch)
	{
		if (*(cpu_type_t*)swap(&(temp.cputype), &arch[i].cputype,
				sizeof(cpu_type_t)) == CPU_TYPE_X86_64 &&
			*(cpu_subtype_t*)swap(&(temp.cpusubtype), &arch[i].cpusubtype,
					sizeof(cpu_subtype_t)) != 8)
		{
			swap(&(temp.offset), &arch[i].offset, sizeof(uint64_t));
			manager->file += temp.offset;
			manager->fat = 1;
			return (manager->funct(manager));
		}
		i++;
	}
	return (all_fat_64(manager, nfat_arch));
}

int							study_fat_32(t_manager *manager)
{
	struct fat_arch			*arch;
	struct fat_arch			temp;
	uint32_t				nfat_arch;
	uint32_t				i;

	i = 0;
	nfat_arch = get_arch_nb(manager);
	arch = (struct fat_arch*)((void*)manager->file + sizeof(struct fat_header));
	while (i < nfat_arch)
	{
		ft_bzero(&temp, sizeof(struct fat_arch));
		if (*(cpu_type_t*)swap(&(temp.cputype), &arch[i].cputype,
				sizeof(cpu_type_t)) == CPU_TYPE_X86_64 &&
				*(cpu_subtype_t*)swap(&(temp.cpusubtype), &arch[i].cpusubtype,
						sizeof(cpu_subtype_t)) != 8)
		{
			swap(&(temp.offset), &arch[i].offset, sizeof(uint32_t));
			manager->file += temp.offset;
			manager->fat = 1;
			return (manager->funct(manager));
		}
		i++;
	}
	return (all_fat_32(manager, nfat_arch));
}
