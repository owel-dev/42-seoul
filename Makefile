# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 02:56:11 by ulee              #+#    #+#              #
#    Updated: 2021/02/10 04:07:26 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRCS		= ./ft_printf.c 	\
			  ./src_main.c  	\
			  ./src_check.c 	\
			  ./src_set.c   	\
			  ./src_print.c 	\
			  ./src_types.c 	\
			  ./src_types2.c 	\
			  ./src_etc.c		\

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

LIB			= ar rcu

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C ./libft
	cp ./libft/libft.a $(NAME)
	$(LIB) $(NAME) $(OBJS)

all : $(NAME)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)
	
fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
