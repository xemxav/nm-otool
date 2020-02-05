/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   otool_64.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:32:57 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 15:32:57 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/nm_otool.h"

static int				print_text_64(t_manager *manager, uint32_t offset,
		uint64_t size, uint64_t init_adrr)
{
	uint64_t			adr;
	uint8_t				*byte;
	int					y;

	adr = 0;
	byte = (uint8_t*)(manager->file + offset);
	while (101)
	{
		y = 0;
		while (y < 16)
		{
			if (adr == size)
				return (ft_printf("\n"));
			if (y == 0)
				ft_printf("%.16llx\t%.2x ", adr + init_adrr, byte[adr]);
			else
				ft_printf("%.2x ", byte[adr]);
			if (y == 15 && adr < size - 1)
				ft_printf("\n");
			y++;
			adr++;
		}
	}
}

static int				manage_section_64(t_manager *manager,
		struct section_64 *section)
{
	uint32_t			offset;
	uint64_t			size;
	uint64_t			addr;

	ft_memcpy(&offset, &section->offset, sizeof(uint32_t));
	ft_memcpy(&size, &section->size, sizeof(uint64_t));
	ft_memcpy(&addr, &section->addr, sizeof(uint64_t));
	if (manager->swap)
	{
		swap(&offset, &section->offset, sizeof(uint32_t));
		swap(&size, &section->size, sizeof(uint64_t));
		swap(&addr, &section->addr, sizeof(uint64_t));
	}
	if (!manager->lib)
		ft_printf("%s:\nContents of (__TEXT,__text) section\n",
				manager->filename);
	else
		ft_printf("Contents of (__TEXT,__text) section\n");
	if (manager->ppc)
		return (print_text_64_ppc(manager, offset, size, addr));
	return (print_text_64(manager, offset, size, addr));
}

static int				find_text_section_64(t_manager *manager,
		struct segment_command_64	*segment)
{
	struct section_64			*section;
	uint32_t					nsects;
	uint32_t					i;

	i = 0;
	nsects = segment->nsects;
	if (manager->swap)
		ft_memrev(&nsects, sizeof(char), sizeof(uint32_t));
	section = (struct section_64*)((void*)segment +
			sizeof(struct segment_command_64));
	while (i < nsects)
	{
		if (ft_strcmp(section[i].segname, SEG_TEXT) == 0 &&
		ft_strcmp(section[i].sectname, SECT_TEXT) == 0)
			return (manage_section_64(manager, &section[i]));
		i++;
	}
	return (FALSE);
}

int						find_text_64(t_manager *manager)
{
	uint32_t					i;
	struct load_command			*lc;
	struct load_command			lc_temp;
//	struct segment_command_64	*seg;

	i = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		ft_memcpy(&lc_temp, lc, sizeof(struct load_command));
		if (manager->swap)
			swap_lc(&lc_temp, lc);
		if (lc_temp.cmd == LC_SEGMENT_64)
		{
			if (find_text_section_64(manager, (struct segment_command_64*)lc))
				return (TRUE);
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (FALSE);
}
