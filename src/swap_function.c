/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   swap_function.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:48:12 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 12:48:12 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

struct load_command		*swap_lc(struct load_command *temp,
		struct load_command *lc)
{
	swap(&temp->cmd, &lc->cmd, sizeof(u_int32_t));
	swap(&temp->cmdsize, &lc->cmdsize, sizeof(u_int32_t));
	return (temp);
}

struct symtab_command	*swap_symtab(struct symtab_command *temp,
		struct symtab_command *symtab)
{
	swap(&temp->cmd, &symtab->cmd, sizeof(uint32_t));
	swap(&temp->cmdsize, &symtab->cmdsize, sizeof(uint32_t));
	swap(&temp->symoff, &symtab->symoff, sizeof(uint32_t));
	swap(&temp->nsyms, &symtab->nsyms, sizeof(uint32_t));
	swap(&temp->stroff, &symtab->stroff, sizeof(uint32_t));
	swap(&temp->strsize, &symtab->strsize, sizeof(uint32_t));
	return (temp);
}

struct nlist			*swap_nlist(struct nlist *temp, struct nlist *nlist)
{
	temp->n_sect = nlist->n_sect;
	temp->n_type = nlist->n_type;
	swap(&temp->n_un.n_strx, &nlist->n_un.n_strx, sizeof(uint32_t));
	swap(&temp->n_desc, &nlist->n_desc, sizeof(int16_t));
	swap(&temp->n_value, &nlist->n_value, sizeof(uint32_t));
	return (temp);
}

struct nlist_64			*swap_nlist64(struct nlist_64 *temp,
		struct nlist_64 *nlist)
{
	temp->n_sect = nlist->n_sect;
	temp->n_type = nlist->n_type;
	swap(&temp->n_un.n_strx, &nlist->n_un.n_strx, sizeof(uint32_t));
	swap(&temp->n_desc, &nlist->n_desc, sizeof(int16_t));
	swap(&temp->n_value, &nlist->n_value, sizeof(uint64_t));
	return (temp);
}

uint32_t				add_nsect(uint32_t *nsects, int swapping)
{
	uint32_t temp;

	if (swapping)
		return (*(uint32_t*)swap(&temp, nsects, sizeof(uint32_t)));
	else
		return (*nsects);
}
