/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:14 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_game *game, int x, t_ray *ray)
{
	int	y;
	int	color;

	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		color = get_color(game, ray, y);
		put_pixel(&game->img, x, y, color);
	}
}
