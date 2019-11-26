/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nm.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/14 13:16:55 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 13:16:55 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/includes/libft.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct	s_manager
{
	char		*filename;
	char 		*file;
	int 		fd;
	struct stat	buf;
}				t_manager;

typedef struct	s_symbol
{
	uint32_t	*value;
	char 		*sym_type;
	char 		*sym_name;
}				t_symbol;


int 				nm(t_manager *manager);
/*
 *			commons.c
 */
int					usage(char *prog, char *bad_name, char *dirname);
int					get_mapping(t_manager *manager);
int					open_file(char *name, char *prog, int func(t_manager *));

/*
 *			utils.c
 */
int					free_manager(t_manager *manager, int ret);
#endif
