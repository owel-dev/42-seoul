CLANG = clang++
# CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
CLANGFLAGS = 
NAME = out
RM = rm -rf

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

FILES = main \

ifeq ($(DEBUG),true)
	CLANG += -g
endif

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(OBJ_DIR) :
	@mkdir obj

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CLANG) $(CLANGFLAGS) -I $(INC_DIR) -c $< -o $@	

$(NAME): $(OBJS)
	@$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

rb: 

test: fclean all

.PHONY: all clean fclean re test
