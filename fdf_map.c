/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/09 14:24:50 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	size_x(char *argv)
{
	char	*str;
	int		y;
	int		fd;

	str = 0;
	y = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &str))
	{
		y++;
		free(str);
	}
	free(str);
	if (close(fd) == -1)
		return (0);
	return (y);
}

static int	size_y(char *argv)
{
	char	*str;
	char	**split;
	int		x;
	int		fd;

	str = 0;
	x= 0;
	split = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!get_next_line(fd, &str))
		return (0);
	split = ft_split(str, ' ');
	while (split[x])
		x++;
	free(str);
	if (close(fd) == -1)
		return (0);
	return (x);
}

static int	*construct_map(char **split, int width, t_map *map)
{
	int	*values;
	int	i;
	
	i = -1;
	values = malloc(sizeof(int) * width);
	if (!values)
	{
		free(split);
		return (0);
	}	
	while (split[++i])
	{
		values[i] = ft_atoi(split[i]);
		find_min(map, values, i);
	}
	free(split);
	if (i < width)
		return (0);
	return (values);
}

static int	init_map(t_map *map, char *argv)
{
	map->height = size_x(argv);
	map->width = size_y(argv);
	map->matrix = malloc(sizeof(int *) * map -> height);
	if (!(map -> matrix))
		return (0);
	else
		return (1);
}

int	fill_map(char *argv, t_map *map)
{
	char	*str;
	int		i;
	int		fd;

	str = 0;
	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1 || !init_map(map, argv))
		return (0);
	while (get_next_line(fd, &str))
	{
		(map->matrix)[i] = construct_map(ft_split(str, ' '), map -> width, map);
		if (!(map->matrix[i++]))
			return (free(str), free_all(&map->matrix),0);
		free(str);
	}
	if (close(fd) == -1)
		return (0);
	return (free(str), 1);
}
