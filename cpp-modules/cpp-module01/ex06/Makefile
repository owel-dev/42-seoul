# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 15:04:00 by ulee              #+#    #+#              #
#    Updated: 2021/12/27 17:34:34 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror
NAME = filter
RM = rm -f

SRCS = 	main.cpp \
				Karen.cpp
				
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CLANG) $(CLANGFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) test.txt.replace

re: fclean $(NAME)

test: $(NAME)
	@$(addprefix ./, $(NAME)) DEBUG
	@$(addprefix ./, $(NAME)) INFO
	@$(addprefix ./, $(NAME)) WARNING
	@$(addprefix ./, $(NAME)) ERROR
	@make fclean

.PHONY: all clean fclean re test