# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/24 04:34:02 by ahmez-za          #+#    #+#              #
#    Updated: 2022/07/26 22:35:15 by ahmez-za         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = philo.c helper.c
NAME = philo
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -pthread
# FSANITIZ = -fsanitize=thread
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -o $(NAME) $(FSANITIZ) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)
	
re: fclean all