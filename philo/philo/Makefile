# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:08:33 by abkhairi          #+#    #+#              #
#    Updated: 2023/12/28 13:03:49 by abkhairi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRC = philo.c helper.c parsing.c initialisation.c routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

