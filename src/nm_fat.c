/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nm_fat.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 09:18:47 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 09:18:47 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static uint32_t get_arch_nb(t_manager *manager)
{
	struct fat_header	*header;
	uint32_t 			nfat_arch;

	header = (struct fat_header*)manager->file;
	swap(&nfat_arch, &header->nfat_arch, sizeof(uint32_t));
	return nfat_arch;
}

static int	all_fat_64(t_manager *manager, uint32_t nfat_arch_ind)
{
	uint32_t 			offset;
	struct fat_arch_64		*arch;
	int					i;

	i = 0;
	manager->file_tmp = manager->file;
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header) + 1);
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		manager->file += *(uint32_t*)
				(swap(&offset, &arch[i].offset,sizeof(uint32_t)));
		i--;
		if (nm(manager) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

static int	all_fat_32(t_manager *manager, uint32_t nfat_arch_ind)
{
	uint32_t 			offset;
	struct fat_arch		*arch;
	int					i;

	i = 0;
	manager->file_tmp = manager->file;
	arch = (struct fat_arch*)(manager->file + sizeof(struct fat_header) + 1);
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		manager->file += *(uint32_t*)
				(swap(&offset, &arch[i].offset,sizeof(uint32_t)));
		i--;
		if (nm(manager) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

int			study_fat_64(t_manager *manager)
{
	struct fat_arch_64	*arch;
	struct fat_arch_64	*temp;
	uint32_t 			nfat_arch;
	int					i;

	i = 0;
	nfat_arch = get_arch_nb(manager);
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch)
	{
		if (*(cpu_type_t*)swap(&temp.cputype, &arch[i].cputype,
				sizeof(cpu_type_t)) == CPU_TYPE_X86_64)
			swap(&temp.offset, &arch[i].offset, sizeof(uint64_t));
		i++;
	}
	if (temp.offset)
		manager->file += temp.offset;
	else
		return (all_fat_64(manager, nfat_arch));
	return (nm(manager));
}

//void		print_arch_struct(struct fat_arch arch)
//{
//	cpu_type_t	cputype;	/* cpu specifier (int) */
//	cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
//	uint32_t	offset;		/* file offset to this object file */
//	uint32_t	size;		/* size of this object file */
//	uint32_t	align;
//
//	swap(&cputype, &arch.cputype,sizeof(cpu_type_t));
//	swap(&cpusubtype, &arch.cpusubtype,sizeof(cpu_type_t));
//	swap(&offset, &arch.offset,sizeof(cpu_type_t));
//	swap(&size, &arch.size,sizeof(cpu_type_t));
//	swap(&align, &arch.align,sizeof(cpu_type_t));
//	ft_printf("cputype =%d, cpusub=%d, offset=%d, size = %d, align = %d\n",
//		   cputype, cpusubtype, offset, size, align);
//
//}

int			study_fat_32(t_manager *manager)
{
	struct fat_arch	*arch;
	struct fat_arch  temp;
	uint32_t 			nfat_arch;
	uint32_t			i;

	i = 0;
	ft_bzero(&temp, sizeof(struct fat_arch));
	nfat_arch = get_arch_nb(manager);
	arch = (struct fat_arch*)((void*)manager->file + sizeof(struct fat_header));
	while (i < nfat_arch)
	{
		if (*(cpu_type_t*)swap(&temp.cputype, &arch[i].cputype, sizeof(cpu_type_t))
			== CPU_TYPE_X86_64)
			swap(&temp.offset, &arch[i].offset,sizeof(uint32_t));
		i++;
	}
	if (temp.offset)
		manager->file += temp.offset;
	else
		return (all_fat_32(manager, nfat_arch));
	return (nm(manager));
}

// faire un fonction qui etudie le header et renvoie le nombre d'arch

//int			study_fat_32(t_manager *manager)
//{
//	struct fat_header	*header;
//	struct fat_arch		*arch;
//	uint32_t 			tmp;
//	uint32_t 			tmp2;
//	cpu_type_t 			tmp3;
//	int 				i;
//
//	i = 0;
//	if (!manager->file_tmp)
//		manager->file_tmp = manager->file;
//	header = (struct fat_header*)manager->file_tmp;
//	if (swap(&tmp, &header->nfat_arch, sizeof(uint32_t)) == NULL)
//		return (ERROR);
//	arch = (struct fat_arch*)(header + 1);
//	while (i < tmp)
//	{
//		if (*(cpu_type_t*)swap(&tmp3, &arch[i].cputype, sizeof(cpu_type_t))
//			== CPU_TYPE_X86_64)
//		{
//			manager->file = manager->file_tmp +
//							*(uint32_t*)(swap(&tmp2, &arch[i].offset,sizeof(uint32_t)));
//			return (nm(manager));
//		}
//		i++;
//	}
//	manager->file = manager->file_tmp;
//	return (TRUE);
//}