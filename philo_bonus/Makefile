# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 18:33:31 by ulee              #+#    #+#              #
#    Updated: 2021/10/16 18:03:06 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

FILE = 	0_philo_bonus\
		1_routines_bonus\
		2_utils_bonus \
		3_monitor_bonus \
		4_arg_bonus

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
