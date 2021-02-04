NAME		= libftprintf.a

SRCS		= ./ft_printf.c \
			  ./src_libft.c \
			  ./src_check.c \
			  ./src_set.c \
			  ./src_print.c \
			  ./src_types.c \

OBJS		= $(SRCS:.c=.o)

RM			= rm -f
LIB			= ar rcu
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C ./libft
	cp ./libft/libft.a $(NAME)
	$(LIB) $(NAME) $(OBJS)

all : $(NAME)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re




# NAME = a.out

# FILES = ft_printf src_check src_libft src_print src_set src_types
# FILES_O = $(addsuffix .o, $(FILES))

# all : $(FILES_O) main.o
# 	gcc -o $(NAME) $^

# t : $(FILES_O) test.o
# 	gcc -o $(NAME) $^

# c :
# 	rm *.o *.out

# re : c all
	