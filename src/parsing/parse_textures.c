/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 16:29:20 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_color(char *color_str)
{
	char	**rgb;
	int		r, g, b;
	int		color;

	rgb = split_string(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		free_split(rgb);
		return (-1);
	}
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = create_rgb_color(r, g, b);
	return (color);
}

static char	*trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 0)
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = 0;
	return (str);
}

int	parse_textures(t_game *game, char *line)
{
	char	*trimmed;
	char	*path;

	trimmed = trim_whitespace(line);
	if (strncmp(trimmed, "NO ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		game->north_texture = strdup(path);
	}
	else if (strncmp(trimmed, "SO ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		game->south_texture = strdup(path);
	}
	else if (strncmp(trimmed, "WE ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		game->west_texture = strdup(path);
	}
	else if (strncmp(trimmed, "EA ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		game->east_texture = strdup(path);
	}
	else if (strncmp(trimmed, "F ", 2) == 0)
	{
		path = trim_whitespace(trimmed + 2);
		game->floor_color = parse_color(path);
		if (game->floor_color == -1)
			return (1);
	}
	else if (strncmp(trimmed, "C ", 2) == 0)
	{
		path = trim_whitespace(trimmed + 2);
		game->ceiling_color = parse_color(path);
		if (game->ceiling_color == -1)
			return (1);
	}
	return (0);
}
