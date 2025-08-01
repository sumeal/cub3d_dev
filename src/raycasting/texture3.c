/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:58:18 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_bounds(t_ray *ray, int tex_y)
{
	if (ray->tex_num < 0 || ray->tex_num >= 4)
		return (0);
	if (ray->tex_x < 0 || ray->tex_x >= TEX_WIDTH)
		return (0);
	if (tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0);
	return (1);
}

static int	shade_wall(int color, t_ray *ray)
{
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int	get_color(t_game *game, t_ray *ray, int y)
{
	int	tex_y;
	int	color;

	(void)y;
	tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
	ray->tex_pos += ray->step;
	if (!check_bounds(ray, tex_y))
		return (0);
	if (!game->textures[ray->tex_num].texture)
		return (0);
	if (!game->textures[ray->tex_num].texture[tex_y])
		return (0);
	color = game->textures[ray->tex_num].texture[tex_y][ray->tex_x];
	return (shade_wall(color, ray));
}
