/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   study_lib.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xem <xem@student.le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/24 13:26:48 by xem          #+#   ##    ##    #+#       */
/*   Updated: 2019/12/24 13:26:48 by xem         ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ranlib.h>
#include "../includes/ft_nm.h"

int		study_lib(t_manager *manager)
{
	struct ar_hdr	*lib;
	struct	ranlib  *rlib;
	long size;
	int size_name;

	lib = (struct ar_hdr*)(manager->file + SARMAG);
	size_name = ft_atoi(lib->ar_name + 3);
	printf("size_name = %d\n", size_name);
	size = (long)((void*)lib + size_name);
	printf("size = %#lx\n", size);
	rlib = (struct	ranlib*)((void*)lib + sizeof(struct ar_hdr) + size_name + sizeof(long) * 2);
	printf("ran_strx = %lld\n,ran_name= %s, ran_off = %lld", rlib->ran_un.ran_strx, rlib->ran_un.ran_name, rlib->ran_off);
	return (TRUE);
}
