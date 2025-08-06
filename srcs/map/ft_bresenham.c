/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:47 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/06 11:10:30 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_over_limit(t_3d p);
static void	draw_line_h(t_3d p1, t_3d p2, t_data *data, int dir);
static void	draw_line_v(t_3d p1, t_3d p2, t_data *data, int dir);

void	draw_line(t_3d p1, t_3d p2, t_data *data)
{
	int		dir;
	int		condition;
	t_3d	diff;
	t_3d	p3;

	if (is_over_limit(p1) && is_over_limit(p2))
		return ;
	p3 = p1;
	condition = fabs(p2.x - p1.x) > fabs(p2.y - p1.y);
	if ((p1.x > p2.x && condition) || (p1.y > p2.y && !condition))
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if ((diff.y < 0 && condition) || (diff.x < 0 && !condition))
		dir = -1;
	if (condition && diff.x != 0)
		draw_line_h(p1, p2, data, dir);
	if (!condition && diff.y != 0)
		draw_line_v(p1, p2, data, dir);
}

static int	is_over_limit(t_3d p)
{
	if (fabs(p.x) > WIDTH && fabs(p.y) > HEIGHT)
		return (1);
	return (0);
}

static void	draw_line_h(t_3d p1, t_3d p2, t_data *data, int dir)
{
	t_3d	diff;
	double	dz;
	int		y;
	int		i;
	int		p;
	unsigned int	color;

	diff = subtrate_3d_points(p2, p1);
	dz = (p2.z - p1.z) / fabs(diff.x);
	y = p1.y;
	p = 2 * diff.y - diff.x;
	i = -1;
	while (++i <= diff.x)
	{
		color = interpolate_color(p1.color, p2.color, i, diff.x);
		my_mlx_pixel_put(data, p1.x + i, y, color, p1.z + dz * i);
		if (p > 0)
		{
			y += dir;
			p -= 2 * diff.x;
		}
		p += 2 * fabs(diff.y);
	}
}

static void	draw_line_v(t_3d p1, t_3d p2, t_data *data, int dir)
{
	t_3d	diff;
	double	dz;
	int		x;
	int		i;
	int		p;
	unsigned int	color;

	diff = subtrate_3d_points(p2, p1);
	dz = (p2.z - p1.z) / fabs(diff.y);
	x = p1.x;
	p = 2 * diff.x - diff.y;
	i = -1;
	while (++i <= diff.y)
	{
		color = interpolate_color(p1.color, p2.color, i, diff.y);
		my_mlx_pixel_put(data, x, p1.y + i, color, p1.z + dz * i);
		if (p > 0)
		{
			x += dir;
			p -= 2 * diff.y;
		}
		p += 2 * fabs(diff.x);
	}
}

