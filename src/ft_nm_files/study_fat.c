/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   study_fat.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 13:00:05 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 13:00:05 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

t_arch_name g_name_list[] = {
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

uint32_t				get_arch_nb(t_manager *manager)
{
	struct fat_header		*header;
	uint32_t				nfat_arch;

	header = (struct fat_header*)manager->file;
	swap(&nfat_arch, &header->nfat_arch, sizeof(uint32_t));
	return (nfat_arch);
}

char					*get_arch_name(cpu_type_t type)
{
	int i;

	i = 0;
	while (g_name_list[i].name != NULL)
	{
		if (g_name_list[i].cputype == type)
			return (g_name_list[i].name);
		i++;
	}
	return (NULL);
}
