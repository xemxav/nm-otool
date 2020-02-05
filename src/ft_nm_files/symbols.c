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

#include "../../includes/nm_otool.h"

void			print_symbols_64(t_manager *manager)
{
	t_symbol	*symbol;

	symbol = manager->symbol_list;
	while (symbol != NULL)
	{
		if (!check_string(symbol->sym_name))
			return ;
		if (symbol->sym_type != 'u' && symbol->sym_type != 'U' &&
		symbol->sym_type != 'i' && symbol->sym_type != 'I')
			ft_printf("%.16llx", symbol->value64);
		else
			ft_printf("%16c", ' ');
		if (symbol->sym_type == 'i' || symbol->sym_type == 'I')
			ft_printf(" %c %s (indirect for %s)\n", symbol->sym_type,
					symbol->sym_name, symbol->sym_name);
		else
			ft_printf(" %c %s\n", symbol->sym_type, symbol->sym_name);
		symbol = symbol->next;
	}
}

void			print_symbols_32(t_manager *manager)
{
	t_symbol	*symbol;

	symbol = manager->symbol_list;
	while (symbol != NULL)
	{
		if (!check_string(symbol->sym_name))
			return ;
		if (symbol->sym_type != 'u' && symbol->sym_type != 'U' &&
		symbol->sym_type != 'i' && symbol->sym_type != 'I')
			ft_printf("%.8x", symbol->value32);
		else
			ft_printf("%8c", ' ');
		if (symbol->sym_type == 'i' || symbol->sym_type == 'I')
			ft_printf(" %c %s (indirect for %s)\n",
					symbol->sym_type, symbol->sym_name, symbol->sym_name);
		else
			ft_printf(" %c %s\n", symbol->sym_type, symbol->sym_name);
		symbol = symbol->next;
	}
}

static void		insert_symbol(t_manager *manager, t_symbol *new)
{
	t_symbol	*first;
	t_symbol	*second;
	int			ret;

	first = NULL;
	ret = 0;
	second = manager->symbol_list;
	while (second != NULL &&
	(ret = ft_strcmp(second->sym_name, new->sym_name)) <= 0)
	{
		if (ret == 0 && ((!new->is64 && new->value32 < second->value32)
		|| (new->is64 && new->value64 < second->value64)))
			break ;
		first = second;
		second = second->next;
	}
	new->next = second;
	if (first)
		first->next = new;
	else
		manager->symbol_list = new;
}

int				record_symbol(t_manager *manager, t_symbol *symbol)
{
	t_symbol	*new;

	if ((new = (t_symbol*)malloc(sizeof(t_symbol))) == NULL)
		return (ERROR);
	ft_memcpy(new, symbol, sizeof(t_symbol));
	new->next = NULL;
	if (manager->symbol_list == NULL)
		manager->symbol_list = new;
	else
		insert_symbol(manager, new);
	return (TRUE);
}
