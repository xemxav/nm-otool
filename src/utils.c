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

int		free_manager(t_manager *manager)
{
	if (munmap(manager.file, manager->buf.st_size) < 0)
		return (ERROR);
	return (TRUE);
}