/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/27 19:01:39 by nsaraiva         ###   ########.fr       */
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
	{
		free(split[x]);
		x++;
	}
	free(split);
	while (str)
	{
		free(str);
		get_next_line(fd, &str);
	}
	if (close(fd) == -1)
		return (0);
	return (x);
}

static t_3d newPoint3d(int x, int y, int z)
{
	t_3d	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

static unsigned int	get_color(char *split)
{
	unsigned int	color;

	color = COLOR;
	while (*split && *split != ',')
		split++;
	if (*split == ',')
	{
		split++;
		color = ft_atoi_base(split, 16);
	}
	return (color);

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
		values[i] = newPoint3d(i, x, ft_atoi(split[i]));
		values[i] = ft_transformation(values[i], map->projection);
		values[i].color = get_color(split[i]);
		find_min(map, values[i]);
		free(split[i]);
	}
	while (split[i])
		free(split[i++]);
	free(split);
	if (i < map->width)
		return (0);
	return (values);
}

static int	init_map(t_map *map, char *argv)
{
	map->height = size_x(argv);
	if (!map->height)
		return (0);
	map->width = size_y(argv);
	if (!map->width)
		return (0);
	map->matrix = malloc(sizeof(t_3d *) * (map->height));
	if (!(map->matrix))
		return (0);
	else
		return (1);
}

int	fill_map(char *argv, t_map *map)
{
	char	*str;
	char	**split;
	int		i;
	int		fd;

	str = 0;
	i = 0;
	if (!init_map(map, argv))
		return (0);
	fd = open(argv, O_RDONLY);
	if (!fd)
		return (0);
	while (get_next_line(fd, &str))
	{
		split = ft_split(str, ' ');
		(map->matrix)[i] = construct_map(split, map, i);
		if (!(map->matrix[i++]))
			return (free(str), free_map(map), 0);
		free(str);
	}
	if (close(fd) == -1)
		return (0);
	return (free(str), 1);
}
