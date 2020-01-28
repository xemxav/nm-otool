/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ppc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:27:08 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 17:27:08 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/nm_otool.h"

static void				by_byte_32_ppc(t_manager *manager, int y,
		uint32_t *byte, uint32_t adr)
{
	uint32_t			temp;

	ft_memcpy(&temp, byte, sizeof(uint32_t));
	if (manager->swap)
		swap(&temp, byte, sizeof(uint32_t));
	if (y == 0)
		ft_printf("%.8llx\t%.8x ", adr, temp);
	else
		ft_printf("%.8x ", temp);
}

int						print_text_32_ppc(t_manager *manager, uint32_t offset,
											uint32_t size, uint32_t init_addr)
{
	uint32_t			adr;
	uint32_t			*byte;
	uint32_t			*end;
	int					y;

	adr = 0;
	byte = (uint32_t*)(manager->file + offset);
	end = (uint32_t*)(manager->file + offset + size);
	while (101)
	{
		y = 0;
		while (y < 4)
		{
			if (byte == end)
				return (TRUE);
			by_byte_32_ppc(manager, y, byte, adr + init_addr);
			y++;
			byte++;
		}
		adr += 16;
		ft_printf("\n");
	}
}

static void				by_byte_64_ppc(t_manager *manager, int y,
		uint32_t *byte, uint64_t adr)
{
	uint32_t			temp;

	ft_memcpy(&temp, byte, sizeof(uint32_t));
	if (manager->swap)
		swap(&temp, byte, sizeof(uint32_t));
	if (y == 0)
		ft_printf("%.16llx\t%.8x ", adr, temp);
	else
		ft_printf("%.8x ", temp);
}

int						print_text_64_ppc(t_manager *manager, uint32_t offset,
		uint32_t size, uint64_t init_addr)
{
	uint64_t			adr;
	uint32_t			*byte;
	uint32_t			*end;
	int					y;

	adr = 0;
	byte = (uint32_t*)(manager->file + offset);
	end = (uint32_t*)(manager->file + offset + size);
	while (101)
	{
		y = 0;
		while (y < 4)
		{
			if (byte == end)
				return (TRUE);
			by_byte_64_ppc(manager, y, byte, adr + init_addr);
			y++;
			byte++;
		}
		adr += 16;
		ft_printf("\n");
	}
}
