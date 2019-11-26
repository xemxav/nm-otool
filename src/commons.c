/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   commons.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 15:08:06 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/21 15:08:06 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			usage(char *prog, char *bad_name, char *dirname)
{
	if (bad_name)
		fd_printf(2, "%s: %s: No such file or directory.\n", prog, bad_name);
	if (dirname)
		fd_printf(2, "%s: %s: Is a directory.\n", prog, dirname);
	return (TRUE);
}

int		get_mapping(t_manager *manager)
{
	if ((manager->file = (char*)mmap(0, (size_t)manager->buf.st_size,
									 PROT_READ, MAP_PRIVATE, manager->fd, 0)) == MAP_FAILED)
		return (ERROR);
	return (TRUE);
}

int		open_file(char *name, char *prog, int func(t_manager *))
{
	t_manager	manager;
	int			ret;

	ret = TRUE;
	ft_bzero(&manager, sizeof(t_manager));
	manager.filename = name;
	if ((manager.fd = open(name, O_RDONLY)) < 0)
		return (usage(prog, name, NULL));
	if (fstat(manager.fd, &(manager.buf)) < 0)
		ret = ERROR;
	if (ret != ERROR && S_ISDIR(manager.buf.st_mode))
		return (free_manager(&manager, usage(prog, NULL, name)));
	if (ret != ERROR)
		ret = get_mapping(&manager);
	if (ret != ERROR)
		func(&manager);
	return (free_manager(&manager, ret));
}