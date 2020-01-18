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
# include <mach/machine.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>

#define SECT "tdb"

typedef struct				s_symbol
{
	uint64_t				value;
	char 					sym_type;
	char 					*sym_name;
	struct s_symbol			*next;
}							t_symbol;

typedef struct				s_libfile
{
	char					*filename;
	char 					*file_start;
	uint64_t 				offset;
	struct s_libfile		*next;
}							t_libfile;

typedef struct				s_manager
{
	char					*filename;
	char 					*file;
	char 					*file_tmp;
	int 					fd;
	struct stat				buf; //verifier si besoin de le garder dans le manager
	int 					swap;
	struct symtab_command	symtab;
	size_t					header_size;
	uint32_t				ncmds;
	struct s_symbol 		*symbol_list;
	struct s_libfile		*libstart;
}							t_manager;




int 				nm(t_manager *manager);
void				study_type(t_symbol *symbol, uint8_t type);
/*
 *			commons.c
 */
int					usage(char *prog, char *bad_name, char *dirname);
int					get_mapping(t_manager *manager);
int					open_file(char *name, char *prog, int func(t_manager *));
/*
 *			nm_64.c
 */
int 				read_symtab_64(t_manager *manager);
/*
 *			nm_32.c
 */
int 				read_symtab_32(t_manager *manager);
/*
 *			nm_fat.c
 */
int					study_fat_64(t_manager *manager);
int					study_fat_32(t_manager *manager);
/*
 *			study_lib.c
 */
int					study_lib(t_manager *manager);
/*
 *			print_lib.c
 */
int					record_libfile(t_manager *manager, t_libfile *libfile);
int   				iterate_on_libfile(t_manager *manager);

/*
 *			symbols_64.c
 */
int					record_symbol(t_manager *manager, t_symbol *symbol);
void				print_symbols_64(t_manager *manager);
void				print_symbols_32(t_manager *manager);
/*
 *			utils.c
 */
struct load_command *swap_lc(struct load_command *temp, struct load_command *lc);
struct symtab_command *swap_symtab(struct symtab_command *temp,
								   struct symtab_command *symtab);
struct nlist *swap_nlist(struct nlist *temp, struct nlist *nlist);
struct nlist_64 *swap_nlist64(struct nlist_64 *temp, struct nlist_64 *nlist);
uint32_t add_nsect(uint32_t *nsects, int swap);

/*
 *			utils.c
 */
void 				*swap(void *tmp, void *value, size_t size);
int					free_manager(t_manager *manager, int ret);
t_symbol 			*free_symbols(t_symbol *head);
#endif
