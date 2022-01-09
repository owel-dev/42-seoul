CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = animal
RM = rm -f

SRCS = 	main.cpp \
				Animal.cpp \
				Dog.cpp \
				Cat.cpp \
				Brain.cpp
				
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