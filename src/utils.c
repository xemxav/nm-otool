/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/18 18:53:03 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 18:53:03 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		free_manager(t_manager *manager, int ret)
{
	if (manager->file)
	{
		if (munmap(manager->file, (size_t)manager->buf.st_size) < 0)
			ret = ERROR;
	}
	close(manager->fd);
	return (ret);
}