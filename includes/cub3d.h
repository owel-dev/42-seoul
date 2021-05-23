/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:37:48 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 12:17:57 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "struct.h"
# include "mecro.h"

void	parsing(t_info *io);
void	init_player(t_player *player);
void	init_parse_info(t_info *io);
void	parse_file(t_info *io);

void	parse_line(t_info *io, char *line);
int		type_line(char *line);
int		is_tex(char *line);
int		is_map(char *line);

void	parse_resolution(t_info *io, char *line);
void	set_screen(t_info *io, char **size);

void	parse_texture(t_info *io, char *line, int flag);
void	check_dup_texture(t_info *io, int flag);
void	check_xpm(char *line);

void	parse_color(t_info *io, char *line, int flag);
void	check_color_count(char *map);
void	check_color_space(char *map);
void	check_color_value(t_info *io, char **color, int flag);
void	make_color(t_info *io, char **color, int flag);
int		arr_len(char **arr);

void	parse_map(t_info *io, char *line);
void	check_option(t_info *io);
void	link_map(t_info *io, char *line);
void	make_map(t_info *io);
void	check_map(t_info *io);
void	check_space_path(char **path);

void	find_player(t_info *io);
void	find_sprite(t_info *io);
char	*ft_strdup_blank(t_info *io, char *str);
void	dfs_map(t_info *io, char **map, int x, int y);
void	duplicate_map(t_info *io);

void	set_sprite(t_info *io);
void	set_pos_sprite(t_info *io, int i, int x, int y);

void	ray_casting(t_info *io);
void	init_arr(t_info *io);
void	init_player_dir(t_info *io);
void	rotate_player(t_player *player, double rot_speed);
void	init_key(t_info *io);

void	init_buffer(t_info *info);
void	init_texture(t_info *info);
void	load_texture(t_info *info);

void	check_texture_file_exists(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
void	ft_free(void *s);

void	wall_cast(t_info *io);
void	init_ray(t_info *io, t_player *player, t_ray *ray, int x);
void	cast_floor_ceiling(t_info *io);
void	set_step_first(t_ray *ray, t_player *player);
void	cast_ray(t_info *io, t_ray *ray);
void	get_perp_dist(t_ray *ray, t_player *player);
void	set_draw_height(t_info *io, t_ray *ray);
void	get_wall_texture(t_player *player, t_ray *ray);
void	get_wall_color(t_info *io, t_ray *ray, int x);

void	sprite_cast(t_info *io);
void	sort_sprite(t_info *io, t_player *player);
void	sort(t_info *info);
void	translate_sprite(\
	t_info *io, t_player *player, t_sprite_ray *s_ray, int i);
void	calculate_sprite_height(t_info *io, t_sprite_ray *s_ray);
void	calculate_sprite_width(t_info *io, t_sprite_ray *s_ray);
void	get_sprite_color(t_info *io, t_sprite_ray *s_ray, int stripe);

int		save_bmp(t_info *io);
void	ft_bfile(t_info *io, int fd);
void	ft_binfo(t_info *io, int fd);
void	ft_bdata(t_info *io, int fd);

int		main_loop(t_info *io);
void	draw_image(t_info *info);

void	make_window_hook(t_info *io);
void	key_update(t_info *io);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *io);

int		ft_exit(int ret);
void	print_error(char *log);
void	arr_free(char **arr);
void	list_free(t_info *io);
void	del_list(void *content);
void	free_cub(t_info *io);
int		check_argu(char *argu);

#endif
