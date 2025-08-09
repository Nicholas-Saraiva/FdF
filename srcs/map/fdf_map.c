/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/05 18:39:19 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	init_map(t_map *map, char *argv);
static t_3d	*construct_map(char **split, t_map *map, int x);

int	fill_map(char *argv, t_map *map)
{
	char	*str;
	char	**split;
	int		i;
	int		fd;

	str = 0;
	i = 0;
	init_map(map, argv);
	fd = open(argv, O_RDONLY);
	if (!fd)
		return (0);
	while (get_next_line(fd, &str))
	{
		split = ft_split(str, ' ');
		(map->matrix)[i] = construct_map(split, map, i);
		if (!(map->matrix[i++]))
			return (free(str),
			ft_error_map("First line is not the smalest or malloc failed",map), 0);
		free(str);
	}
	if (close(fd) == -1)
		return (0);
	return (free(str), 1);
}

static int	init_map(t_map *map, char *argv)
{
	map->height = get_height(argv);
	if (!map->height)
		ft_error_map("Getting Height of map failed", map);
	map->width = get_width(argv);
	if (!map->width)
		ft_error_map("Getting Width of map failed", map);
	map->matrix = ft_calloc((map->height), sizeof(t_3d *));
	if (!(map->matrix))
		ft_error_map("malloc on matrix failed", map);
	return (1);
}

static t_3d	*construct_map(char **split, t_map *map, int x)
{
	t_3d	*values;
	int		i;

	i = -1;
	values = malloc(sizeof(t_3d) * map->width);
	if (!values)
		return (0);
	while (split[++i] && i < map->width)
	{
		values[i] = new_point3d(i, x, ft_atoi(split[i]));
		values[i].color = get_color(values[i], split[i]);
		values[i] = map->projection(values[i]);
		find_limits(map, values[i]);
		free(split[i]);
	}
	while (split[i])
		free(split[i++]);
	free(split);
	if (i < map->width)
	{
		free(values);
		return (0);
	}
	return (values);
}
