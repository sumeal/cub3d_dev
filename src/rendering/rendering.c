/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:12 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*src;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		return (*(unsigned int*)src);
	}
	return (0);
}

static void	clear_top(t_game *game, int *buffer, int total_pixels)
{
	int	i;

	i = -1;
	while (++i < total_pixels / 2)
		buffer[i] = game->ceiling_color;
}

static void	clear_bottom(t_game *game, int *buffer, int total_pixels)
{
	int	i;

	i = total_pixels / 2 - 1;
	while (++i < total_pixels)
		buffer[i] = game->floor_color;
}

void	render(t_game *game)
{
	int	*buffer;
	int	total_pixels;

	buffer = (int*)game->img.addr;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	clear_top(game, buffer, total_pixels);
	clear_bottom(game, buffer, total_pixels);
	shoot_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
