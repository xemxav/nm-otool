/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   symbol_64.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 15:35:01 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 15:35:01 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			print_symbols_64(t_manager *manager)
{
	t_symbol	*symbol;
	t_symbol	*tmp;

	symbol = manager->symbol_list;
	while (symbol != NULL)
	{
		if (symbol->sym_type != 'u' && symbol->sym_type != 'U')
			ft_printf("%.16llx", symbol->value);
		else
			ft_printf("%16c", ' ');
		ft_printf(" %c %s\n", symbol->sym_type, symbol->sym_name);
		tmp = symbol;
		symbol = symbol->next;
		free(tmp);
	}
	manager->symbol_list = NULL;
}

static void		insert_symbol_64(t_manager *manager, t_symbol *new)
{
	t_symbol	*first;
	t_symbol	*second;

	first = NULL;
	second = manager->symbol_list;
	while (second != NULL && ft_strcmp(second->sym_name, new->sym_name) <= 0)
	{
		first = second;
		second = second->next;
	}
	if (second != NULL && ft_strcmp(second->sym_name, new->sym_name) == 0 &&
	new->value > second->value)
	{
		first = second;
		second = second->next;
	}
	new->next = second;
	if (first)
		first->next = new;
	else
		manager->symbol_list = new;
}

int				record_symbol_64(t_manager *manager, t_symbol *symbol)
{
	t_symbol	*new;

	if ((new = (t_symbol*)malloc(sizeof(t_symbol))) == NULL)
		return (ERROR);
	ft_memcpy(new, symbol, sizeof(t_symbol));
	if (manager->symbol_list == NULL)
		manager->symbol_list = new;
	else
	{
		insert_symbol_64(manager, new);
	}
	return (TRUE);
}
