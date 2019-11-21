/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nm.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:01:13 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:01:13 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int 		nm(t_manager *manager)
{
	printf("coucou\n");
	return (TRUE);
}

int			main(int ac, char **av)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (ac == 1)
		ret = open_file("a.out", "ft_nm", &nm);
	else
	{
		while (i < ac && ret != ERROR)
		{
			ret = open_file(av[i], "ft_nm", &nm);
			i++;
		}
	}
	return (ret);
}


