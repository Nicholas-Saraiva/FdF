/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/02 19:06:00 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_height(char *argv)
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

static int	get_width(char *argv)
{
	char	*str;
	char	**split;
	int		x;
	int		fd;

	str = 0;
	split = 0;
	x = -1;
	fd = open(argv, O_RDONLY);
	if (fd == -1 || !get_next_line(fd, &str))
		return (0);
	split = ft_split(str, ' ');
	free(str);
	while (split[++x])
		free(split[x]);
	while (get_next_line(fd, &str))
		free(str);
	if (close(fd) == -1)
		return (free(split), 0);
	return (free(split), x);
}

static t_3d newPoint3d(int x, int y, int z)
{
	t_3d	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

static unsigned int	get_color(t_3d point, char *split)
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
	else if (point.z > 0)
	{
		color = ((int) point.z * 40 << 16) | ((int) point.z * 2 << 8) | ((int) point.z * 20 +  0x91);
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
		values[i].color = get_color(values[i], split[i]);
		values[i] = map->projection(values[i]);
		find_min(map, values[i]);
		free(split[i]);
	}
	while (split[i])
		free(split[i++]);
	free(split);
	if (i < map->width)
		ft_error("Size Invalid");
	return (values);
}

static int	init_map(t_map *map, char *argv)
{
	map->height = get_height(argv);
	if (!map->height)
		return (0);
	map->width = get_width(argv);
	if (!map->width)
		return (0);
	map->matrix = malloc(sizeof(t_3d *) * (map->height));
	map->total_lines = (map->width - 1) * map->height + (map->height - 1) * map->width;
	if (!(map->matrix))
		return (0);
	else
		return (1);
}
static double	get_depth(t_3d p1, t_3d p2)
{
	return ((p1.z + p2.z) / 2.0f);
}

int	compare_lines(const void *a, const void *b)
{
	double depth_a; 
	double depth_b;
   
	depth_a = ((t_line *)a)->depth;
	depth_b = ((t_line *)b)->depth;
	if (depth_a < depth_b)
		return (-1);
	if (depth_a > depth_b)
		return (1);
	return (0);
}

static void	connect_lines(t_map *map)
{
	t_line	*lines;
	t_3d	p;
	t_3d	p2;
	int		i;
	int		j;
	int		count;
	int		total;
   

	i = -1;
	count = 0;
	total = map->total_lines;
	lines = malloc(sizeof(t_line) * map->total_lines);
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			p = map->matrix[i][j];
			if (j < map->width - 1)
			{
				p2 = map->matrix[i][j + 1];
				lines[count++] = (t_line){i, j, i, j + 1, p, p2, get_depth(p, p2)};
			}
			if (i < map->height - 1)
			{
				p2 = map->matrix[i + 1][j];
				lines[count++] = (t_line){i, j, i + 1, j, p, p2, get_depth(p, p2)};
			}
		}
	}
	qsort(lines, count, sizeof(t_line), compare_lines);
	map->line = lines;
	map->total_lines = total;
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
	connect_lines(map);
	if (close(fd) == -1)
		return (0);
	return (free(str), 1);
}
