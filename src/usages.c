/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   usages.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/18 17:41:01 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 17:41:01 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			usage(char prog,char *bad_name)
{
	fd_printf(2, "%s: %s: No such file or directory\n", prog, bad_name);
	return (TRUE);
}