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

int			study_fat_64(t_manager *manager)
{
	struct fat_header		*header;
	struct fat_arch_64		*arch;
	uint32_t 				tmp;
	uint64_t 				tmp2;
	cpu_type_t 				tmp3;
	int 					i;

	i = 0;
	if (!manager->file_tmp)
		manager->file_tmp = manager->file;
	header = (struct fat_header*)manager->file_tmp;
	if (swap(&tmp, &header->nfat_arch, sizeof(uint32_t)) == NULL)
		return (ERROR);
	arch = (struct fat_arch_64*)(header + 1);
	while (i < tmp)
	{
		if (*(cpu_type_t*)swap(&tmp3, &arch[i].cputype,sizeof(cpu_type_t))
			== CPU_TYPE_X86_64)
		{
			manager->file = manager->file_tmp +
					*(uint64_t*)(swap(&tmp2, &arch[i].offset,sizeof(uint64_t)));
			return (nm(manager));
		}
		i++;
	}
	manager->file = manager->file_tmp;
	return (TRUE);
}

int			study_fat_32(t_manager *manager)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	uint32_t 			tmp;
	uint32_t 			tmp2;
	cpu_type_t 			tmp3;
	int 				i;

	i = 0;
	if (!manager->file_tmp)
		manager->file_tmp = manager->file;
	header = (struct fat_header*)manager->file_tmp;
	if (swap(&tmp, &header->nfat_arch, sizeof(uint32_t)) == NULL)
		return (ERROR);
	arch = (struct fat_arch*)(header + 1);
	while (i < tmp)
	{
		if (*(cpu_type_t*)swap(&tmp3, &arch[i].cputype,sizeof(cpu_type_t))
		== CPU_TYPE_X86_64)
		{
			manager->file = manager->file_tmp +
					*(uint32_t*)(swap(&tmp2, &arch[i].offset,sizeof(uint32_t)));
			return (nm(manager));
		}
		i++;
	}
	manager->file = manager->file_tmp;
	return (TRUE);
}