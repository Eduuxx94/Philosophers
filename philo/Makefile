# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 08:39:14 by ede-alme          #+#    #+#              #
#    Updated: 2022/08/13 11:57:31 by ede-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC_NAME = main.c \
			threads.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc
CFLAGS = -g -fsanitize=$(FLAG) -lpthread -Wall -Wextra -Werror
FLAG = thread

ARGS = 5 100 30 30

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)
valgrind: fclean 
	gcc -g -Wall -Wextra -Werror -pthread -I $(INC_PATH) $(SRC) -o ./philo
	valgrind -s --leak-check=full --show-leak-kinds=all ./philo $(ARGS)
	@echo "---> Finished valgrind test with $(ARGS) ARGS <---"

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re