/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nm.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:01:13 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:01:13 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		get_mapping(t_manager *manager)
{
	void	*ptr;

	if ((manager->file = (char*)mmap(0, manager->buf.st_size,
			PROT_READ, MAP_PRIVATE, manager->fd, 0) == MAP_FAILED)
		return (ERROR);
	return (TRUE);
}


static int		nm(char *name);
{
	t_manager	manager;

	ft_bzero(&manager, sizeof(t_manager));
	manger.filename = name;
	if ((manager.fd = open(name, O_RDONLY)) < 0)
		return usage("ft_nm", name);
	if (fstat(manager.fd, &(manager.buf)) < 0)
		return (ERROR);
	if ((get_mapping(&manager) == ERROR)
		return (ERROR);
	if (mummap());
	return (free_manager(&manager));
}

int			main(int ac, char **av)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (ac == 1)
		ret = nm("a.out");
	else
	{
		while (i < ac && ret != ERROR)
		{
			ret = nm(av[i]);
			i++;
		}
	}
	return (ret);
}


