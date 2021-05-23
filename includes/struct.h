/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:40:48 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:48:09 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			distance;
}					t_sprite;

typedef struct		s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
}					t_ray;

typedef struct		s_sprite_ray
{
	double			x;
	double			y;
	double			inversion_detection;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				v_move_screen;
	int				height;
	int				width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
}					t_sprite_ray;

typedef struct		s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct		s_key
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}					t_key;

typedef struct		s_info
{
	void			*mlx;
	void			*win;
	t_list			*li;
	t_img			img;
	t_player		player;
	t_ray			ray;
	t_sprite_ray	s_ray;
	t_key			key;
	t_sprite		*sprite;
	int				**buf;
	double			*z_buffer;
	int				**texture;
	int				width;
	int				height;
	int				map_width;
	int				map_height;
	int				invalid_map;
	char			**map;
	char			**dup_map;
	int				is_map;
	char			*north_file;
	char			*south_file;
	char			*west_file;
	char			*east_file;
	char			*sprite_file;
	int				floor_color;
	int				ceiling_color;
	int				dir;
	int				num_sprite;
	int				is_save;
	int				fd;
	int				max_width;
	int				max_height;
}					t_info;

#endif
