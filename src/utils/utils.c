/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:16 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	
	i = -1;
	while (++i < 256)
		game->keys[i] = 0;
	game->key_left = 0;
	game->key_right = 0;
	
	i = -1;
	while (++i < 4)
	{
		game->textures[i].img.img = NULL;
		game->textures[i].texture = NULL;
	}
}

int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
