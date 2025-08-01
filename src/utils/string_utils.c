/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/30 21:48:20 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_delimiters(char *str, char delimiter)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = -1;
	len = strlen(str);
	while (++i < len)
	{
		if (str[i] == delimiter)
			count++;
	}
	return (count + 1);
}

static void	copy_substring(char **result, char *str, int start, int end, int count)
{
	result[count] = malloc(end - start + 1);
	strncpy(result[count], str + start, end - start);
	result[count][end - start] = '\0';
}

char	**split_string(char *str, char delimiter)
{
	char	**result;
	int		count;
	int		i;
	int		start;
	int		len;

	count = count_delimiters(str, delimiter);
	result = malloc(sizeof(char*) * (count + 1));
	if (!result)
		return (NULL);
	count = 0;
	start = 0;
	len = strlen(str);
	i = -1;
	while (++i <= len)
	{
		if (str[i] == delimiter || str[i] == '\0')
		{
			copy_substring(result, str, start, i, count);
			count++;
			start = i + 1;
		}
	}
	result[count] = NULL;
	return (result);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
