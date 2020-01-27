/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   otool_32.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 13:25:23 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 13:25:23 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static int				print_text_32(t_manager *manager, uint32_t offset,
		uint32_t size)
{
	uint32_t			adr;
	uint8_t				*byte;
	int					y;

	adr = 0;
	byte = (uint8_t*)(manager->file + offset);
	ft_printf("%s:\nContents of (__TEXT,__text) section\n",
			manager->filename);
	while (101)
	{
		y = 0;
		while (y < 16)
		{
			if (adr == size)
				return (ft_printf("\n"));
			if (y == 0)
				ft_printf("%.8llx\t%.2x ", adr, byte[adr]);
			if (y == 15)
				ft_printf("%.2x \n", byte[adr]);
			if (y > 0 && y < 15)
				ft_printf("%.2x ", byte[adr]);
			y++;
			adr++;
		}
	}
}

static int				manage_section_32(t_manager *manager,
		struct section *section)
{
	uint32_t			offset;
	uint32_t			size;

	ft_memcpy(&offset, &section->offset, sizeof(uint32_t));
	ft_memcpy(&size, &section->size, sizeof(uint32_t));
	if (manager->swap)
	{
		swap(&offset, &section->offset, sizeof(uint32_t));
		swap(&size, &section->size, sizeof(uint32_t));
	}
	return (print_text_32(manager, offset, size));
}

static int				find_text_section_32(t_manager *manager,
		struct segment_command	*segment)
{
	struct section				*section;
	uint32_t					nsects;
	int							i;

	i = 0;
	nsects = segment->nsects;
	if (manager->swap)
		ft_memrev(&nsects, sizeof(char), sizeof(uint32_t));
	section = (struct section*)((void*)segment +
			sizeof(struct segment_command));
	while (i < nsects)
	{
		if (ft_strcmp(section[i].segname, SEG_TEXT) == 0 &&
		ft_strcmp(section[i].sectname, SECT_TEXT) == 0)
			return (manage_section_32(manager, &section[i]));
		i++;
	}
	return (FALSE);
}

int						find_text_32(t_manager *manager)
{
	int							i;
	struct load_command			*lc;
	struct load_command			lc_temp;

	i = 0;
	lc = (struct load_command*)((void*)manager->file + manager->header_size);
	while (i < manager->ncmds)
	{
		ft_memcpy(&lc_temp, lc, sizeof(struct load_command));
		if (manager->swap)
			swap_lc(&lc_temp, lc);
		if (lc_temp.cmd == LC_SEGMENT)
		{
			return (find_text_section_32(manager,
					(struct segment_command*)lc));
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (FALSE);
}
