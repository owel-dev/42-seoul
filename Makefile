# NAME		= libftprintf.a

# SRCS		= ./ft_printf.c \
# 			  ./ft_printf_utils.c \

# OBJS		= $(SRCS:.c=.o)

# RM			= rm -f
# LIB			= ar rcu
# CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME) : $(OBJS)
# 	make all -C ./libft
# 	cp ./libft/libft.a $(NAME)
# 	$(LIB) $(NAME) $(OBJS)

# all : $(NAME)

# clean :
# 	make clean -C ./libft
# 	$(RM) $(OBJS)

# fclean : clean
# 	make fclean -C ./libft
# 	$(RM) $(NAME)

# re : fclean all

# .PHONY: all clean fclean re

NAME = a.out

FILES = ft_printf src_check src_libft src_print src_set src_types
FILES_O = $(addsuffix .o, $(FILES))

all : $(FILES_O) main.o
	gcc -o $(NAME) $^

c :
	rm *.o *.out