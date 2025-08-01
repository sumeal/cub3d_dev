/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:21 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static void	set_player_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

static void	set_player_south(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

static void	set_player_east(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

static void	set_player_west(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}

static int	check_map_borders(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = 0;
		while (game->map[i] && game->map[i][j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == 'N' ||
				game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
				game->map[i][j] == 'W')
			{
				if (i == 0 || i == game->map_height - 1)
					return (0);
				if (j == 0 || j == (int)strlen(game->map[i]) - 1)
					return (0);
			}
			j++;
		}
	}
	return (1);
}

static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
		set_player_north(game);
	else if (direction == 'S')
		set_player_south(game);
	else if (direction == 'E')
		set_player_east(game);
	else if (direction == 'W')
		set_player_west(game);
}

static int	process_player_position(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
		game->map[i][j] == 'E' || game->map[i][j] == 'W')
	{
		game->player.pos_x = j + 0.5;
		game->player.pos_y = i + 0.5;
		set_player_direction(game, game->map[i][j]);
		return (1);
	}
	return (0);
}

int	find_player_start(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (++i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			player_count += process_player_position(game, i, j);
			j++;
		}
	}
	return (player_count == 1 ? 0 : 1);
}

int	validate_map(t_game *game)
{
	if (!game->north_texture || !game->south_texture ||
		!game->west_texture || !game->east_texture)
	{
		printf("Error\nMissing texture paths\n");
		return (1);
	}
	if (game->floor_color == -1 || game->ceiling_color == -1)
	{
		printf("Error\nInvalid color values\n");
		return (1);
	}
	if (!check_map_borders(game))
	{
		printf("Error\nMap is not properly closed\n");
		return (1);
	}
	if (find_player_start(game) != 0)
	{
		printf("Error\nInvalid player position\n");
		return (1);
	}
	return (0);
}
