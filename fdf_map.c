/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/04 01:00:39 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static size_t array_len(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static size_t array_len_int(int *n)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}*/

/*static void	free_all(char **str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_array_len(str);
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}*/

static int	size_y(char *argv)
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

static int	size_x(char *argv)
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

static int	*atoi_array(char **split, int width)
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
		values[i] = ft_atoi(split[i]);
	free(split);
	if (i < width)
		return (0);
	return (values);
}

int	fill_map(char *argv, t_matrix *map)
{
	char	*str;
	char	**split;
	int		i;
	int		fd;

	str = 0;
	split = 0;
	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (0);
	map -> height = size_y(argv);
	map -> width = size_x(argv);
	map -> matrix = malloc(sizeof(int *) * map -> height);
	if (!(map -> matrix))
		return (0);
	while (get_next_line(fd, &str))
	{
		(map -> matrix)[i] = atoi_array(ft_split(str, ' '), map -> width);
		if (!(map -> matrix[i++]))
			return (free(str), free(split), 0);
		free(str);
	}
	if (close(fd) == -1)
		return (0);
	return (free(str), 1);
}
