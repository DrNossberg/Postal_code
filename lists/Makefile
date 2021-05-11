##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## compile the List lib
##


CC			:= gcc
NAME		:= liblist.a
FILE_TYPE	:= c
OUTPUT_DIR	:= ..
SRC_DIR 	:= src
OBJ_DIR		:= obj
SRC 		:= $(wildcard $(SRC_DIR)/*.$(FILE_TYPE))
OBJ			:= $(SRC:$(SRC_DIR)/%.$(FILE_TYPE)=$(OBJ_DIR)/%.o)
CFLAGS		:= -I ./include -W -Wextra -Wall -g

ifeq ($(MAKECMDGOALS),leaks)
CFLAGS		+=	-g3
else
CFLAGS		+=	-g0
endif

all		: create_objfolder $(NAME)

$(NAME)	: $(OBJ)
	ar rc $(NAME) $(OBJ)
ifeq (,$(findstring $(OUTPUT_DIR),"."))
	mv $(NAME) $(OUTPUT_DIR)/$(NAME)
endif

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(FILE_TYPE)
	$(CC) $(CFLAGS) $(CINCS) -o $@ -c $^

clean	:
	rm -f $(OBJ)
	rm -df $(OBJ_DIR)

fclean	: clean
	rm -f $(OUTPUT_DIR)/$(NAME)

create_objfolder:
	@mkdir -p $(OBJ_DIR)

re		: fclean all

leaks	: re
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(OUTPUT_DIR)/$(NAME)

.PHONY	: all clean fclean re
