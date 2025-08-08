/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:47 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 14:39:55 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_over_limit(t_3d p);
static void	draw_line_h(t_3d p1, t_3d p2, t_data *data, int dir);
static void	draw_line_v(t_3d p1, t_3d p2, t_data *data, int dir);

void	draw_line(t_3d p1, t_3d p2, t_data *data)
{
	t_3d	p_tmp;
	int		is_gentle_slope;
	t_3d	diff;
	int		dir;

	if (is_over_limit(p1) && is_over_limit(p2))
		return ;
	p_tmp = p1;
	is_gentle_slope = (fabs(p2.x - p1.x) > fabs(p2.y - p1.y));
	if ((is_gentle_slope && p1.x > p2.x) || (!is_gentle_slope && p1.y > p2.y))
	{
		p1 = p2;
		p2 = p_tmp;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if ((is_gentle_slope && diff.y < 0) || (!is_gentle_slope && diff.x < 0))
		dir = -1;
	if (is_gentle_slope && diff.x != 0)
		draw_line_h(p1, p2, data, dir);
	else if (!is_gentle_slope && diff.y != 0)
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
	t_line			line;
	int				y;
	unsigned int	color;

	line.diff = subtrate_3d_points(p2, p1);
	line.dz = (p2.z - p1.z) / fabs(line.diff.x);
	y = p1.y;
	line.p = 2 * line.diff.y - line.diff.x;
	line.i = 0;
	while (line.i <= line.diff.x)
	{
		color = interpolate_color(p1.color, p2.color, line.i, line.diff.x);
		my_mlx_pixel_put(data, (t_3d){(int)p1.x + line.i, (int)y, p1.z
			+ line.dz * line.i, color});
		if (line.p > 0)
		{
			y += dir;
			line.p -= 2 * line.diff.x;
		}
		line.p += 2 * fabs(line.diff.y);
		line.i++;
	}
}

static void	draw_line_v(t_3d p1, t_3d p2, t_data *data, int dir)
{
	t_line			line;
	int				x;
	unsigned int	color;

	line.diff = subtrate_3d_points(p2, p1);
	line.dz = (p2.z - p1.z) / fabs(line.diff.y);
	x = p1.x;
	line.p = 2 * line.diff.x - line.diff.y;
	line.i = 0;
	while (line.i <= line.diff.y)
	{
		color = interpolate_color(p1.color, p2.color, line.i, line.diff.y);
		my_mlx_pixel_put(data, (t_3d){(int)x, (int)p1.y + line.i, p1.z
			+ line.dz * line.i, color});
		if (line.p > 0)
		{
			x += dir;
			line.p -= 2 * line.diff.y;
		}
		line.p += 2 * fabs(line.diff.x);
		line.i++;
	}
}
