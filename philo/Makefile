# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 18:33:31 by ulee              #+#    #+#              #
#    Updated: 2021/10/16 17:27:35 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

FILE = 	0_philo\
		1_routines\
		2_utils \
		3_arg

SRCS = $(addprefix ./, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(LIBFT) $(OBJS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
