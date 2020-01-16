/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   study_lib.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/24 13:26:48 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2019/12/24 13:26:48 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include "../includes/ft_nm.h"

int get_name_size(struct ar_hdr	*lib_header)
{
	if (lib_header->ar_name[0] == '#')
		return (ft_atoi(lib_header->ar_name + 3));
	else
		return (ft_atoi(lib_header->ar_name));
}

char *get_name(struct ar_hdr	*lib_header, int size)
{
	if (size < 17)
		return lib_header->ar_name;
	else
		return (char*)((void*)lib_header + sizeof(struct ar_hdr));
}



void	check_rlib(t_manager *manager, struct	ranlib  *rlib, uint32_t size_rlibs)
{
	struct ar_hdr	*file_header;
	char *file_name;
	int name_size;

	file_header = (struct ar_hdr*)(manager->file + rlib->ran_off);
	name_size = get_name_size(file_header);
	file_name = get_name(file_header, name_size);
	printf("%s(%s):\n", manager->filename, file_name);
	manager->file = (char*)((void*)file_header + sizeof(struct ar_hdr) + name_size);
	nm(manager);
}

void	iterate_on_rlibs(t_manager *manager, struct	ranlib  *rlib, uint32_t size_rlibs)
{
	size_t i;

	i = 0;
//	while (i < size_rlibs / sizeof(struct ar_hdr))
//	{
		check_rlib(manager, &rlib[i], size_rlibs);
//		i++;
//	}
}

int		study_lib(t_manager *manager)
{
	//penser a faire avec le _64
	struct ar_hdr	*lib_header;
	struct	ranlib  *rlib;
	uint32_t	nb_rlib;
	int size_name;

	lib_header = (struct ar_hdr*)(manager->file + SARMAG);
	size_name = get_name_size(lib_header);
	nb_rlib = *(uint32_t*)((void*)lib_header + sizeof(struct ar_hdr) + size_name);
	rlib = (struct ranlib*)((void*)lib_header + sizeof(struct ar_hdr) + size_name + sizeof(uint32_t));
	iterate_on_rlibs(manager, rlib, nb_rlib);
	return (0);
}
