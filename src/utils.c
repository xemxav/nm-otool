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

//faire une fonction to_swap qui appelle swap si besoin et prend que deux param

void		*swap(void *tmp, void *value, size_t size)
{
	ft_memcpy(tmp, value, size);
	if (ft_memrev(tmp, sizeof(char), size) == NULL)
		return (NULL);
	return (tmp);
}

void		*ts(void *tmp, void *value, size_t size, int ts)
{
	if (ts)
		return swap(tmp, value, size);
	return value;
}

t_symbol		*free_symbols(t_symbol *head)
{
	t_symbol	*tmp;

	if (!head)
		return (NULL);
	tmp = head->next;
	free(head);
	return (free_symbols(tmp));
}

int				free_manager(t_manager *manager, int ret)
{
	if (manager->file)
	{
		if (munmap(manager->file, (size_t)manager->buf.st_size) < 0)
			ret = ERROR;
	}
	if (manager->symbol_list)
		free_symbols(manager->symbol_list);
	close(manager->fd);
	return (ret);
}
