/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/08/07 11:48:48 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x = game->player.dir_x;
	double	old_plane_x = game->player.plane_x;

	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/08/07 11:46:47 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_player_movement(t_game *game)
{
	double move_speed;
	
	move_speed = MOVE_SPEED;
	
	if (game->keys[KEY_W])
	{
		game->player.pos_x += game->player.dir_x * move_speed;
		game->player.pos_y += game->player.dir_y * move_speed;
	}
	if (game->keys[KEY_S])
	{
		game->player.pos_x -= game->player.dir_x * move_speed;
		game->player.pos_y -= game->player.dir_y * move_speed;
	}
	if (game->keys[KEY_A])
	{
		game->player.pos_x -= game->player.plane_x * move_speed;
		game->player.pos_y -= game->player.plane_y * move_speed;
	}
	if (game->keys[KEY_D])
	{
		game->player.pos_x += game->player.plane_x * move_speed;
		game->player.pos_y += game->player.plane_y * move_speed;
	}
}

void handle_player_rotation(t_game *game)
{
	double rot_speed;
	
	rot_speed = ROT_SPEED;
	
	if (game->key_left)
		rotate_player(game, -rot_speed);
	if (game->key_right)
		rotate_player(game, rot_speed);
}

void move_player(t_game *game)
{
	handle_player_movement(game);
	handle_player_rotation(game);
}

