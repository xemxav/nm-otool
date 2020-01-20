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
//		ft_printf(" %c %s sect=%d, type=%x, segment=%s, section=%s\n", symbol->sym_type, symbol->sym_name, symbol->n_sect, symbol->n_type, symbol->segment, symbol->section);
		tmp = symbol;
		symbol = symbol->next;
		free(tmp);
	}
	manager->symbol_list = NULL;
}

void			print_symbols_32(t_manager *manager)
{
	t_symbol	*symbol;
	t_symbol	*tmp;

	symbol = manager->symbol_list;
	while (symbol != NULL)
	{
		if (symbol->sym_type != 'u' && symbol->sym_type != 'U')
			ft_printf("%.8llx", symbol->value);
		else
			ft_printf("%8c", ' ');
		ft_printf(" %c %s\n", symbol->sym_type, symbol->sym_name);
//		ft_printf(" %c %s sect=%d, type=%x, segment=%s, section=%s\n", symbol->sym_type, symbol->sym_name, symbol->n_sect, symbol->n_type, symbol->segment, symbol->section);
		tmp = symbol;
		symbol = symbol->next;
		free(tmp);
	}
	manager->symbol_list = NULL;
}

static void		insert_symbol(t_manager *manager, t_symbol *new)
{
	t_symbol	*first;
	t_symbol	*second;
	int			ret;

	first = NULL;
	ret = 0;
	second = manager->symbol_list;
	while (second != NULL && (ret = ft_strcmp(second->sym_name, new->sym_name)) <= 0)
	{
		if (ret == 0 && new->value < second->value)
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
