/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:19 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_rows(t_texture *texture)
{
	int	j;

	j = -1;
	while (++j < TEX_HEIGHT)
		if (texture->texture[j])
			free(texture->texture[j]);
}

static void	cleanup_single_texture(t_game *game, int i)
{
	if (game->textures[i].img.img)
		mlx_destroy_image(game->mlx, game->textures[i].img.img);
	if (game->textures[i].texture)
	{
		free_texture_rows(&game->textures[i]);
		free(game->textures[i].texture);
	}
}

void	cleanup_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		cleanup_single_texture(game, i);
}

void	cleanup_texture_paths(t_game *game)
{
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
}
