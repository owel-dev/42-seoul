# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 15:04:00 by ulee              #+#    #+#              #
#    Updated: 2021/12/27 17:26:49 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror
NAME = zombie
RM = rm -f

SRCS = 	main.cpp \
				Zombie.cpp \
				newZombie.cpp \
				randomChump.cpp \
		
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

re: fclean $(NAME)

test: $(NAME)
	$(addprefix ./, $(NAME))
	@make fclean

.PHONY: all clean fclean re test