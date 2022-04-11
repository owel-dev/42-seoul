# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 20:52:05 by ulee              #+#    #+#              #
#    Updated: 2022/04/11 13:24:50 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = c++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_containers
RM = rm -rf

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

FILES = main

ifeq ($(DEBUG),true)
	CLANG += -g
endif

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(OBJ_DIR) :
	@mkdir obj

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CLANG) $(CLANGFLAGS) -I $(INC_DIR) -c $< -o $@	

$(NAME): $(OBJS)
	$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: clean $(NAME)

.PHONY: all clean fclean re test
