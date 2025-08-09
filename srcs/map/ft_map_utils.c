/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:08 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 14:47:10 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *argv)
{
	char	*str;
	int		y;
	int		fd;

	str = 0;
	y = 0;
	fd = 0;
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

int	get_width(char *argv)
{
	char	*str;
	char	**split;
	int		x;
	int		fd;

	str = 0;
	split = 0;
	x = -1;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!get_next_line(fd, &str))
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

unsigned int	get_color(t_3d point, char *split)
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
	else if (point.z >= 0)
	{
		color = ((int) point.z * 40 << 16)
			| ((int) point.z * 2 << 8) | ((int) point.z * 20 + 0x91);
	}
	return (color);
}
