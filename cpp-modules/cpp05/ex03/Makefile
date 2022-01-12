CLANG = clang++
CLANGFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = form
RM = rm -f

SRCS = 	main.cpp \
				Bureaucrat.cpp \
				Form.cpp \
				GradeException.cpp \
				ShrubberyCreationForm.cpp \
				RobotomyRequestForm.cpp \
				PresidentialPardonForm.cpp \
				Intern.cpp
				
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