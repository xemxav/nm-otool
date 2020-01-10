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

#include "../includes/ft_nm.h"

int		study_lib(t_manager *manager)
{
	struct ar_hdr	*lib;

	lib = (struct ar_hdr*)(manager->file + SARMAG);
	printf("%s\n%zu\n", lib->ar_name, ft_strlen(lib->ar_name));

	return (TRUE);
}
