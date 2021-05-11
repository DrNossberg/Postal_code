##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## compile the jetpack2Teck3
##


CC			:= gcc
NAME		:= postal
FILE_TYPE	:= c
OBJ_TYPE	:= o

OUTPUT_DIR	:= .
SRC_DIR 	:= src
OBJ_DIR		:= obj

SRC 		:= $(wildcard $(SRC_DIR)/*.$(FILE_TYPE)) \
				$(wildcard $(SRC_DIR)/utils/*.$(FILE_TYPE))
OBJ			:= $(SRC:$(SRC_DIR)/%.$(FILE_TYPE)=$(OBJ_DIR)/%.$(OBJ_TYPE))

CFLAGS		:= -I ./include -W -Wextra -Wall -g
LFLAGS		:= -L. liblist.a

# LFLAGS		:= -L ../utils/ -lutils -l c_graph_prog

ifeq ($(MAKECMDGOALS),leaks)
CFLAGS		+=	-g3
else
CFLAGS		+=	-g0
endif

all		: create_objfolder $(NAME)

$(NAME)	: lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LFLAGS)
ifeq (,$(findstring $(OUTPUT_DIR),"."))
	mv $(NAME) $(OUTPUT_DIR)/$(NAME)
endif

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(FILE_TYPE)
	$(CC) $(CFLAGS)  -o $@ -c $^

lib		:
	make -C lists/

lib_clean:
	make clean -C lists/

lib_fclean:
	make fclean -C lists/

clean	:
	rm -f $(OBJ)
	[ -d $(OBJ_DIR) ] && rm -d $(OBJ_DIR) || true

fclean	: clean
	[ -f ./$(OUTPUT_DIR)/$(NAME) ] && rm -f ./$(OUTPUT_DIR)/$(NAME) || true

create_objfolder:
	@mkdir -p $(OBJ_DIR)

re		: fclean all

leaks	: re
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(OUTPUT_DIR)/$(NAME)

.PHONY	: all clean fclean re
