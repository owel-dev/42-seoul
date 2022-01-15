CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = data
RM = rm -rf

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

FILES = main \
				Base \
				A \
				B \
				C

ifeq ($(DEBUG),true)
	CLANGFLAGS += -g
endif

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CLANG) $(CLANGFLAGS) -I $(INC_DIR) -c $< -o $@	

all: $(NAME)

$(NAME): $(OBJS)
	@$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

test: $(NAME)
	$(addprefix ./, $(NAME))

.PHONY: all clean fclean re test