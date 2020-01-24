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

void		print_arch_struct(struct fat_arch arch)
{
	cpu_type_t	cputype;	/* cpu specifier (int) */
	cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
	uint32_t	offset;		/* file offset to this object file */
	uint32_t	size;		/* size of this object file */
	uint32_t	align;

	swap(&cputype, &arch.cputype,sizeof(cpu_type_t));
	swap(&cpusubtype, &arch.cpusubtype,sizeof(cpu_type_t));
	swap(&offset, &arch.offset,sizeof(cpu_type_t));
	swap(&size, &arch.size,sizeof(cpu_type_t));
	swap(&align, &arch.align,sizeof(cpu_type_t));
ft_printf("cputype =%d, cpusub=%d, offset=%x, size = %d, align = %d\n",
			  cputype, cpusubtype, offset, size, align);

}

static uint32_t get_arch_nb(t_manager *manager)
{
	struct fat_header	*header;
	uint32_t 			nfat_arch;

	header = (struct fat_header*)manager->file;
	swap(&nfat_arch, &header->nfat_arch, sizeof(uint32_t));
	return nfat_arch;
}

char	*get_arch_name(cpu_type_t type)
{
	t_arch_name list[] ={
			{CPU_TYPE_MC680x0, "mc680x0"},
			{CPU_TYPE_X86, "i386"},
			{CPU_TYPE_MC98000, "mc98000"},
			{CPU_TYPE_HPPA, "hppa"},
			{CPU_TYPE_ARM, "armv7"},
			{CPU_TYPE_ARM64, "arm64"},
			{CPU_TYPE_X86_64, "x86_64"},
			{CPU_TYPE_MC88000, "MC88000"},
			{CPU_TYPE_SPARC, "sparc"},
			{CPU_TYPE_I860, "i860"},
			{CPU_TYPE_POWERPC, "ppc"},
			{CPU_TYPE_POWERPC64, "ppc64"},
			{0, NULL}
	};
	int i;
	char	*a_name;

	a_name = NULL;
	i = 0;
	while (list[i].name != NULL)
	{
		if (list[i].cputype == type)
			return (list[i].name);
		i++;
	}
//		a_name = (list[i].cputype == type) ? list[i].name : NULL;
	return (NULL);
}

void 	print_file_arch_name(t_manager *manager, cpu_type_t *cputype)
{
	char 	*a_name;
	cpu_type_t type;

	swap(&type, cputype, sizeof(cpu_type_t));
	a_name = get_arch_name(type);
	if (a_name)
		ft_printf("\n%s (for architecture %s):\n", manager->filename, a_name);
	else
		ft_printf("\n%s (for architecture ):\n", manager->filename);
}

static int	all_fat_64(t_manager *manager, uint32_t nfat_arch_ind)
{
	uint32_t 			offset;
	struct fat_arch_64		*arch;
	int					i;

	i = 0;
	manager->file_tmp = manager->file;
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		manager->file += *(uint32_t*)
				(swap(&offset, &arch[i].offset,sizeof(uint32_t)));
		print_file_arch_name(manager, &arch[i].cputype);
		if (nm(manager) != TRUE)
			return (ERROR);
		i++;
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
	arch = (struct fat_arch*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch_ind)
	{
		manager->file = manager->file_tmp;
		swap(&offset, &arch[i].offset,sizeof(uint32_t));
		manager->file += offset;
//		ft_printf("offsset 1 =%x\n", offset);
//		print_arch_struct(arch[i]);
		print_file_arch_name(manager, &arch[i].cputype);
		if (nm(manager) != TRUE)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int			study_fat_64(t_manager *manager)
{
	struct fat_arch_64	*arch;
	struct fat_arch_64	temp;
	uint32_t 			nfat_arch;
	int					i;

	i = 0;
	ft_bzero(&temp, sizeof(struct fat_arch));
	nfat_arch = get_arch_nb(manager);
	arch = (struct fat_arch_64*)(manager->file + sizeof(struct fat_header));
	while (i < nfat_arch)
	{
		if (*(cpu_type_t*)swap(&(temp.cputype), &arch[i].cputype,
				sizeof(cpu_type_t)) == CPU_TYPE_X86_64)
			swap(&(temp.offset), &arch[i].offset, sizeof(uint64_t));
		i++;
	}
	if (temp.offset)
		manager->file += temp.offset;
	else
		return (all_fat_64(manager, nfat_arch));
	return (nm(manager));
}



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
//		print_arch_struct(arch[i]);
		if (*(cpu_type_t*)swap(&(temp.cputype), &arch[i].cputype, sizeof(cpu_type_t))
			== CPU_TYPE_X86_64)
		{
			swap(&(temp.offset), &arch[i].offset,sizeof(uint32_t));
			break;
		}
		i++;
	}
	if (temp.offset)
		manager->file += temp.offset;
	else
		return (all_fat_32(manager, nfat_arch));
	return (nm(manager));
}
