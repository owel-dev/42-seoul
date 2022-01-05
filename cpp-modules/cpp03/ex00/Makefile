# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 15:04:00 by ulee              #+#    #+#              #
#    Updated: 2022/01/04 13:50:54 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98 -Wshadow
NAME = claptrap
RM = rm -f

SRCS = 	main.cpp \
				ClapTrap.cpp \
				
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
	$(addprefix ./, $(NAME))
	@make fclean

.PHONY: all clean fclean re test