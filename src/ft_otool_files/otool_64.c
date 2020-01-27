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

#include "../../includes/ft_nm.h"

static char				*find_text_section_64(t_manager *manager,
		struct segment_command_64	*segment)
{
	struct section_64			*section;
	uint32_t					nsects;
	int							i;
	uint32_t					offset;
	uint64_t					size;

	i = 0;
	nsects = segment->nsects;
	if (manager->swap)
		ft_memrev(&nsects, sizeof(char), sizeof(uint32_t));
	section = (struct section_64*)((void*)segment +
								   sizeof(struct segment_command_64));
	while (i < nsects)
	{
		if (ft_strcmp(section[i].segname, SEG_TEXT) == 0 && ft_strcmp(section[i].sectname, SECT_TEXT) == 0)
		{
			//si swap faire le swap de size et offset, enregister la size ou alors envoyer a la fonction qui imprime ?		}
			printf("addr = %llx, offset = %x\n", section->addr, section->offset);
		i++
	}
	return (NULL);
}

int					find_text_64(t_manager *manager)
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

		if (lc_temp.cmd == LC_SEGMENT_64)
		{
			find_text_section_64(manager, (struct segment_command_64*)lc);
		}
		lc = (void*)lc + lc_temp.cmdsize;
		i++;
	}
	return (FALSE);
}