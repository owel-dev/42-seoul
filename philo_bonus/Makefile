# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 18:33:31 by ulee              #+#    #+#              #
#    Updated: 2021/10/14 17:26:08 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
INCS = -I../libft -I./
LIBFT = -L../libft -lft
RM = rm -f

FILE = 	0_philo_bonus\
		1_routines_bonus\
		2_utils_bonus

SRCS = $(addprefix ./, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ../libft
	$(CC) $(LIBFT) $(OBJS) -o $@

clean:
	make -C ../libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C ../libft fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
