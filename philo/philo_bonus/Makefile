# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 22:51:05 by abkhairi          #+#    #+#              #
#    Updated: 2023/12/28 13:25:11 by abkhairi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRC = philo_bonus.c heleper_bonus.c parsing_bonus.c initialisation_bonus.c routine_bonus.c

OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
