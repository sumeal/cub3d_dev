/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 20:20:10 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;
	char	buffer[1024];
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		line = buffer;
		while (*line)
		{
			if (*line == '\n')
				count++;
			line++;
		}
	}
	close(fd);
	return (count);
}

static char	*read_line(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos = 0;
	static int	buffer_size = 0;
	char		*line;
	int			line_pos;

	line = malloc(1024);
	if (!line)
		return (NULL);
	line_pos = 0;
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(fd, buffer, sizeof(buffer));
			if (buffer_size <= 0)
				break;
			buffer_pos = 0;
		}
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break;
		}
		line[line_pos++] = buffer[buffer_pos++];
	}
	line[line_pos] = '\0';
	if (line_pos == 0 && buffer_size <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	parse_line(t_game *game, char *line)
{
	if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
		strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
		strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
		return (parse_textures(game, line));
	return (0);
}

static int	is_config_line(char *line)
{
	if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
		strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
		strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	read_map_section(t_game *game, int fd)
{
	char	*line;
	int		i;
	size_t	max_width;

	i = 0;
	max_width = 0;
	while ((line = read_line(fd)) != NULL)
	{
		if (strlen(line) > 0)
		{
			// Skip config lines
			if (!is_config_line(line) && strlen(line) > 0)
			{
				game->map[i] = line;
				if (strlen(line) > max_width)
					max_width = strlen(line);
				i++;
			}
			else
				free(line);
		}
		else
			free(line);
	}
	game->map_height = i;
	game->map_width = max_width;
	return (0);
}

int	parse_map_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (1);
	}
	line_count = count_lines(filename);
	game->map = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map)
		return (1);
	while ((line = read_line(fd)) != NULL)
	{
		if (strlen(line) > 0 && is_config_line(line))
		{
			if (parse_line(game, line) != 0)
			{
				free(line);
				close(fd);
				return (1);
			}
		}
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	read_map_section(game, fd);
	close(fd);
	return (0);
}
