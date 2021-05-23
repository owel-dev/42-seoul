# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 13:40:19 by ulee              #+#    #+#              #
#    Updated: 2021/05/19 11:39:05 by ulee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes -I./libft -I./mlx
LIBFT = -L./libft -lft
MLX = -L./mlx -lmlx
FW = -framework OpenGL -framework AppKit
RM = rm -f

FILE = 	global\
		main\
		check_map\
		dfs_map\
		draw_floor_ceil\
		init_player_dir\
		init_ray\
		load_texture\
		main_loop\
		make_color\
		make_window_hook\
		parse_color\
		parse_file\
		parse_line\
		parse_map\
		parse_texture\
		parsing\
		raycasting\
		sprite_cast\
		type_line\
		wall_cast\
		wall_cast2\
		sort_sprite\
		save_bmp\
		parse_resolution\
		free_cub

SRCS = $(addprefix srcs/, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix srcs/, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME) : $(OBJS)
	make -C ./libft
	make -C ./mlx
	$(CC) $(CFLAGS) $(LIBFT) $(MLX) $(FW) $(OBJS) -o cub3D

all : $(NAME)

clean:
	make -C ./libft clean
	make -C ./mlx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) cub3D
	$(RM) bitmap.bmp
	$(RM) ./libft/libft.a
	$(RM) ./mlx/libmlx.a

re: clean all

.PHONY: all clean fclean re
