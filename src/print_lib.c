/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_lib.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:33:25 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 10:33:25 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int					iterate_on_libfile(t_manager *manager)
{
	t_libfile		*libfile;
	t_libfile		*tmp;

	libfile = manager->libstart;
	manager->file_tmp = manager->file;
	while (libfile != NULL)
	{
		ft_printf("\n%s(%s):\n", manager->filename, libfile->filename);
		manager->file = libfile->file_start;
		if (nm(manager) == ERROR)
			return (ERROR);
		tmp = libfile;
		libfile = libfile->next;
		free(tmp);
	}
	manager->file = manager->file_tmp;
	manager->libstart = NULL;
	return (TRUE);
}

static void			insert_libfile(t_manager *manager, t_libfile *new)
{
	t_libfile		*first;
	t_libfile		*second;

	first = NULL;
	second = manager->libstart;
	while (second != NULL && second->offset <= new->offset)
	{
		first = second;
		second = second->next;
	}
	if (first && first->offset == new->offset)
	{
		free(new);
		return ;
	}
	new->next = second;
	if (first)
		first->next = new;
	else
		manager->libstart = new;
}

int					record_libfile(t_manager *manager, t_libfile *libfile)
{
	t_libfile		*new;

	if ((new = (t_libfile*)malloc(sizeof(t_libfile))) == NULL)
		return (ERROR);
	ft_memcpy(new, libfile, sizeof(t_libfile));
	new->next = NULL;
	if (manager->libstart == NULL)
		manager->libstart = new;
	else
		insert_libfile(manager, new);
	return (TRUE);
}
