.PHONY: all clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = nm_otool
FT_NM = ft_nm
FT_OTOOL = ft_otool

PATH_OBJ = ./obj/
PATH_SRC = ./src/
PATH_INC = ./includes/
PATH_NM = ft_nm_files/
PATH_OTOOL = ft_otool_files/
PATH_SHARED= shared/

HEADER = $(PATH_INC)$(NAME).h

#******************************************************************************#
#                              SHARED                                          #
#******************************************************************************#

PATH_OBJ_SHARED = $(PATH_OBJ)$(PATH_SHARED)
PATH_SRC_SHARED = $(PATH_SRC)$(PATH_SHARED)

FILES_SHARED = commons fat print_lib study_fat study_lib swap_function utils

OBJ_SHARED = $(addprefix $(PATH_OBJ_SHARED), $(addsuffix .o , $(FILES_SHARED)))
SRC_SHARED = $(addprefix $(PATH_SRC_SHARED), $(addsuffix .c , $(FILES_SHARED)))

#******************************************************************************#
#                              FT_NM                                           #
#******************************************************************************#

PATH_OBJ_NM = $(PATH_OBJ)$(PATH_NM)
PATH_SRC_NM = $(PATH_SRC)$(PATH_NM)

FILES_NM = nm_32 nm_64 ft_nm study_type symbols

OBJ_NM = $(addprefix $(PATH_OBJ_NM), $(addsuffix .o , $(FILES_NM)))
SRC_NM = $(addprefix $(PATH_SRC_NM), $(addsuffix .c , $(FILES_NM)))

#******************************************************************************#
#                              FT_OTOOL                                        #
#******************************************************************************#

PATH_OBJ_OTOOL = $(PATH_OBJ)$(PATH_OTOOL)
PATH_SRC_OTOOL = $(PATH_SRC)$(PATH_OTOOL)

FILES_OTOOL = ft_otool otool_32 otool_64 print_ppc

OBJ_OTOOL = $(addprefix $(PATH_OBJ_OTOOL), $(addsuffix .o , $(FILES_OTOOL)))
SRC_OTOOL = $(addprefix $(PATH_SRC_OTOOL), $(addsuffix .c , $(FILES_OTOOL)))

#******************************************************************************#
#                              LIBFT                                           #
#******************************************************************************#

PATH_LIB = ./libft/
PATH_INC_LIB = ./libft/
NAME_LIB = ft
HEADER_LIB = $(PATH_INC_LIB)libft.h
INC_LIB = -L $(PATH_LIB) -l $(NAME_LIB)
LIB = $(PATH_LIB)libft.a


#******************************************************************************#
#                              RULES                                           #
#******************************************************************************#

all: lib $(FT_NM) $(FT_OTOOL)

clean:
	@printf "\n\033[1m SUPPRESSION DES OBJETS\033[0m\n"
	@rm -rf $(PATH_OBJ)
	@make clean -C $(PATH_LIB)

fclean: clean
	@printf "\n\033[1mSUPPRESSION DE $(NAME)\033[0m\n"
	@rm -rf $(FT_OTOOL)
	@rm -rf $(FT_NM)
	@rm -rf $(PATH_OBJ)
	@make fclean -C $(PATH_LIB)

re: fclean all

#******************************************************************************#
#                              Compilation                                     #
#******************************************************************************#

lib:
	@make -C $(PATH_LIB)

$(FT_NM): $(PATH_OBJ) $(PATH_OBJ_SHARED) $(OBJ_SHARED)  $(PATH_OBJ_NM) $(OBJ_NM)
	$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_NM) -I $(PATH_INC) $(INC_LIB) -o $(FT_NM)
	echo "$(FT_NM) has been compiled"

$(FT_OTOOL): $(PATH_OBJ)  $(PATH_OBJ_SHARED) $(OBJ_SHARED) $(PATH_OBJ_OTOOL)  $(OBJ_OTOOL)
	$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_OTOOL)  -I $(PATH_INC) $(INC_LIB) -o $(FT_OTOOL)
	echo "$(FT_OTOOL) has been compiled"

$(PATH_OBJ_SHARED)%.o: $(PATH_SRC_SHARED)%.c $(HEADER) $(LIB)
	$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_OTOOL)%.o: $(PATH_SRC_OTOOL)%.c $(HEADER) $(LIB)
	$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_NM)%.o: $(PATH_SRC_NM)%.c $(HEADER) $(LIB)
	$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

$(PATH_OBJ_SHARED):
	@mkdir -p $(PATH_OBJ_SHARED)

$(PATH_OBJ_OTOOL):
	@mkdir -p $(PATH_OBJ_OTOOL)

$(PATH_OBJ_NM):
	@mkdir -p $(PATH_OBJ_NM)