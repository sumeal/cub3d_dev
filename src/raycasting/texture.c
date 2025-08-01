/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:55:59 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	alloc_tex_mem(t_texture *texture)
{
	int	y;

	texture->texture = malloc(sizeof(int*) * TEX_HEIGHT);
	y = -1;
	while (++y < TEX_HEIGHT)
		texture->texture[y] = malloc(sizeof(int) * TEX_WIDTH);
}

static void	copy_pixels(t_texture *texture, int x, int y)
{
	while (y < TEX_HEIGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			if (x < texture->img.width && y < texture->img.height)
				texture->texture[y][x] = get_pixel_color(&texture->img, x, y);
			else
				texture->texture[y][x] = 0;
		}
		y++;
	}
}

static void	load_one_tex(t_game *game, t_texture *texture, char *path)
{
	texture->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->img.width, &texture->img.height);
	if (!texture->img.img)
	{
		printf("Error: Failed to load texture %s\n", path);
		return;
	}
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	alloc_tex_mem(texture);
	copy_pixels(texture, 0, 0);
}

void	load_textures(t_game *game)
{
	load_one_tex(game, &game->textures[0], game->north_texture);
	load_one_tex(game, &game->textures[1], game->south_texture);
	load_one_tex(game, &game->textures[2], game->west_texture);
	load_one_tex(game, &game->textures[3], game->east_texture);
}

