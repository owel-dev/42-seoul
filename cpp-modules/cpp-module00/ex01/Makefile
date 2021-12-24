# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a_ulee <a_ulee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 20:05:22 by ulee              #+#    #+#              #
#    Updated: 2021/12/25 00:14:09 by a_ulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = phonebook
RM = rm -f

SRCS = 	Phonebook.cpp \
		Contact.cpp \
		main.cpp
		
OBJS = $(SRCS:.cpp=.o)

%.o : %.c
	$(CLANG) $(CLANGFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test: $(NAME)
	./phonebook

.PHONY: all clean fclean re test
