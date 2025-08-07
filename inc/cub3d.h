/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/08/07 11:48:07 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	t_img			img;
	unsigned int	**texture;
}	t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	textures[4];
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color;
	int			ceiling_color;
	int			keys[256];
	int			key_left;
	int			key_right;
}	t_game;

/* Main */
int		main(int argc, char **argv);

/* Parsing */
int		parse_map_file(t_game *game, char *filename);
int		parse_textures(t_game *game, char *line);
int		validate_map(t_game *game);
int		is_valid_map_char(char c);
int		find_player_position(t_game *game);

/* Raycasting */
void	shoot_rays(t_game *game);
void	setup_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	get_wall_dist(t_ray *ray);
void	get_line_height(t_ray *ray);

/* Texture */
void	load_textures(t_game *game);
void	get_tex_coords(t_ray *ray, t_game *game);
int		get_color(t_game *game, t_ray *ray, int y);

/* Rendering */
void	render(t_game *game);
void	draw_line(t_game *game, int x, t_ray *ray);
void	put_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel_color(t_img *img, int x, int y);

/* Game Loop */
int		game_loop(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		close_game(t_game *game);

/* Movement */
void	handle_player_rotation(t_game *game);
void	handle_player_movement(t_game *game);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double angle);
int		is_valid_position(t_game *game, double x, double y);

/* Utils */
void	init_game(t_game *game);
void	cleanup_game(t_game *game);
void	cleanup_textures(t_game *game);
void	cleanup_texture_paths(t_game *game);
void	error_exit(char *message);
int		create_rgb_color(int r, int g, int b);
char	**split_string(char *str, char delimiter);
void	free_split(char **split);

#endif
