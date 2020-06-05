# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/15 15:30:30 by iwillens          #+#    #+#              #
#    Updated: 2020/06/05 14:12:52 by fde-capu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
INCLUDES = -I./includes -I./srcs/libft
CCFLAGS = -Wall -Wextra -Werror

SRC_DIR= ./srcs
OBJ_DIR= ./build
LIBFT = ./srcs/libft

HEADERS =	includes/get_next_line.h \
			includes/minishell_error.h \
			includes/minishell.h \
			includes/typedefs.h

SRCS =  $(SRC_DIR)/parser.c \
		$(SRC_DIR)/parser_keystates.c \
		$(SRC_DIR)/debugs.c		\
		$(SRC_DIR)/minishell.c		\
		$(SRC_DIR)/algos1.c			\
		$(SRC_DIR)/algos2.c			\
		$(SRC_DIR)/listfunctions.c \
		$(SRC_DIR)/prompt.c \
		$(SRC_DIR)/token.c \
		$(SRC_DIR)/token_utils.c \
		$(SRC_DIR)/token_commands.c \
		$(SRC_DIR)/env.c \
		$(SRC_DIR)/com_helpers.c \
		$(SRC_DIR)/exec_helpers.c \
		$(SRC_DIR)/gnl/get_next_line.c \
		$(SRC_DIR)/gnl/get_next_line_utils.c \
		$(SRC_DIR)/error_handling_list.c \
		$(SRC_DIR)/error_handling.c \
		$(SRC_DIR)/args.c \
		$(SRC_DIR)/strops.c \
		$(SRC_DIR)/strops2.c \
		$(SRC_DIR)/syntax.c \
		$(SRC_DIR)/beauty.c \
		$(SRC_DIR)/beauty_eastereggs.c \
		$(SRC_DIR)/keyhooks.c \
 		$(SRC_DIR)/read_line.c \
		$(SRC_DIR)/sequencer.c \
		$(SRC_DIR)/execute.c \
		$(SRC_DIR)/execute_pipes.c \
		$(SRC_DIR)/redirections.c \
		$(SRC_DIR)/filedescriptors.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all : $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CCFLAGS) $(OBJS) $(INCLUDES) -L$(LIBFT) -lft -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)/libft.a $(HEADERS)
	mkdir -p $(OBJ_DIR)/gnl
	$(CC) -c $(CCFLAGS) $< $(INCLUDES) -o $@

$(LIBFT)/libft.a:
	$(MAKE) -C ./srcs/libft
	
clean: 
	rm -rf ./build

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT)

re: fclean all

test:	all
		./$(NAME)

t:		test

rt:		fclean ffclean test

ffclean:	fclean

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

v:		valgrind

rv:		re valgrind

vv:		all valgrind
