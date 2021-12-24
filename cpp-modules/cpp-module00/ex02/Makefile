# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a_ulee <a_ulee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 20:05:22 by ulee              #+#    #+#              #
#    Updated: 2021/12/25 00:18:31 by a_ulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror
NAME = account
RM = rm -f

SRCS = 	Account.cpp \
		test.cpp \
		
OBJS = $(SRCS:.cpp=.o)

%.o : %.c
	$(CLANG) $(CLANGFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) My_account.log

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test: $(NAME)
	./account > My_account.log

.PHONY: all clean fclean re test