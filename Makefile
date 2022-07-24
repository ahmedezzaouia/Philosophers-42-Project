# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/24 04:34:02 by ahmez-za          #+#    #+#              #
#    Updated: 2022/07/24 16:36:17 by sben-chi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = philo.c helper.c
NAME = philo
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
FSANITIZ = -fsanitize=address
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -o $(NAME) $(FSANITIZ)

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)
	
re: fclean all