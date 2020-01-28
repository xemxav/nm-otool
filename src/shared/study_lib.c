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

#include "../../includes/nm_otool.h"

static int				get_name_size(struct ar_hdr	*lib_header)
{
	if (lib_header->ar_name[0] == '#')
		return (ft_atoi(lib_header->ar_name + 3));
	else
		return (0);
}

static char				*get_name(struct ar_hdr	*lib_header, int size)
{
	if (!size)
		return (lib_header->ar_name);
	else
		return (char*)((void*)lib_header + sizeof(struct ar_hdr));
}

static int				iterate_on_rlibs(t_manager *manager,
		struct ar_hdr *ar_header, int size_name)
{
	size_t				i;
	size_t				nb_structs;
	t_libfile			libfile;
	struct ranlib		*rlib;

	i = 0;
	rlib = (struct ranlib*)((void*)ar_header + sizeof(struct ar_hdr)
			+ size_name + sizeof(int));
	nb_structs = *(uint32_t*)((void*)ar_header + sizeof(struct ar_hdr)
			+ size_name) / sizeof(struct ranlib);
	libfile.next = NULL;
	while (i < nb_structs)
	{
		ar_header = (struct ar_hdr*)(manager->file + rlib[i].ran_off);
		size_name = get_name_size(ar_header);
		libfile.offset = rlib[i].ran_off;
		libfile.filename = get_name(ar_header, size_name);
		libfile.file_start = (char*)((void*)ar_header +
				sizeof(struct ar_hdr) + size_name);
		if (record_libfile(manager, &libfile) == ERROR)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

static int				iterate_on_rlibs_64(t_manager *manager,
		struct ar_hdr *ar_header, int size_name)
{
	size_t				i;
	size_t				nb_structs;
	t_libfile			libfile;
	struct ranlib_64	*rlib;

	i = 0;
	rlib = (struct ranlib_64*)((void*)ar_header +
			sizeof(struct ar_hdr) + size_name + sizeof(int));
	nb_structs = *(uint64_t*)((void*)ar_header +
			sizeof(struct ar_hdr) + size_name) / sizeof(struct ranlib);
	libfile.next = NULL;
	while (i < nb_structs)
	{
		ar_header = (struct ar_hdr*)(manager->file + rlib[i].ran_off);
		size_name = get_name_size(ar_header);
		libfile.offset = rlib[i].ran_off;
		libfile.filename = get_name(ar_header, size_name);
		libfile.file_start = (char*)((void*)ar_header +
				sizeof(struct ar_hdr) + size_name);
		if (record_libfile(manager, &libfile) == ERROR)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int						study_lib(t_manager *manager)
{
	struct ar_hdr		*lib_header;
	int					size_name;
	char				*name;
	int					ret;

	ret = 0;
	lib_header = (struct ar_hdr*)(manager->file + SARMAG);
	size_name = get_name_size(lib_header);
	name = get_name(lib_header, size_name);
	manager->lib = 1;
	if (ft_strcmp(name, SYMDEF) == 0 || ft_strcmp(name, SYMDEF_SORTED) == 0)
		ret = iterate_on_rlibs(manager, lib_header, size_name);
	else if (ft_strcmp(name, SYMDEF_64) == 0 ||
	ft_strcmp(name, SYMDEF_64_SORTED) == 0)
		ret = iterate_on_rlibs_64(manager, lib_header, size_name);
	if (ret == ERROR)
		return (ERROR);
	return (iterate_on_libfile(manager));
}
