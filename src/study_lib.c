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

#include "../includes/ft_nm.h"

static int		get_name_size(struct ar_hdr	*lib_header)
{
	if (lib_header->ar_name[0] == '#')
		return (ft_atoi(lib_header->ar_name + 3));
	else
		return (0);
}

static char		*get_name(struct ar_hdr	*lib_header, int size)
{
	if (!size)
		return lib_header->ar_name;
	else
		return (char*)((void*)lib_header + sizeof(struct ar_hdr));
}


static int	iterate_on_rlibs(t_manager *manager, struct	ranlib  *rlib, int size_rlibs)
{
	size_t			i;
	size_t			nb_structs;
	t_libfile		libfile;
	int				name_size;
	struct ar_hdr	*file_header;

	i = 0;
	nb_structs = size_rlibs / sizeof(struct ranlib);
	libfile.next = NULL;
	while (i < nb_structs)
	{
		file_header = (struct ar_hdr*)(manager->file + rlib[i].ran_off);
		name_size = get_name_size(file_header);
		libfile.filename = get_name(file_header, name_size);
		libfile.file_start = (char*)((void*)file_header +
				sizeof(struct ar_hdr) + name_size);
		if (record_libfile(manager, &libfile) == ERROR)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int			study_lib(t_manager *manager)
{
	//penser a faire avec le _64
	struct ar_hdr	*lib_header;
	struct	ranlib  *rlib;
	int	nb_rlib;
	int size_name;

	lib_header = (struct ar_hdr*)(manager->file + SARMAG);
	size_name = get_name_size(lib_header);
	nb_rlib = *(int*)((void*)lib_header + sizeof(struct ar_hdr) + size_name);
	rlib = (struct ranlib*)((void*)lib_header + sizeof(struct ar_hdr) + size_name + sizeof(int));
	if (iterate_on_rlibs(manager, rlib, nb_rlib) == ERROR)
		return (ERROR);
	return (iterate_on_libfile(manager));
}


