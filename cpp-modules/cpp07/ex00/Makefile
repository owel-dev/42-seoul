CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = template
RM = rm -rf

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

FILES = main \

ifeq ($(DEBUG),true)
	CLANGFLAGS += -g
endif

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CLANG) $(CLANGFLAGS) -I $(INC_DIR) -c $< -o $@	

$(OBJ_DIR) :
	@mkdir obj

$(NAME): $(OBJS) 
	@$(CLANG) $(CLANGFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

test: $(NAME)
	$(addprefix ./, $(NAME))
	@make fclean

.PHONY: all clean fclean re test