/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:47 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/25 16:16:23 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_h(t_2d p1, t_data *data, t_2d diff, int dir)
{
	int	y;
	int	i;
	int	p;

	i = 0;
	y = 0;
	p = 0;
	if (diff.x >= 0)
	{
		y = p1.y;
		p = 2 * diff.y - diff.x;
		while (i < diff.x)
		{
			my_mlx_pixel_put(data, p1.x + i, y, p1.color);
			if (p > 0)
			{
				y += dir;
				p -= 2 * diff.x;
			}
			p += 2 * fabs(diff.y);
			i++;
		}
	}
}

static void	draw_line_v(t_2d p1, t_data *data, t_2d diff, int dir)
{
	int	x;
	int	i;
	int	p;

	i = 0;
	x = 0;
	p = 0;
	if (diff.y >= 0)
	{
		x = p1.x;
		p = 2 * diff.x - diff.y;
		while (i < diff.y)
		{
			my_mlx_pixel_put(data, x, p1.y + i, p1.color);
			if (p > 0)
			{
				x += dir;
				p = p - 2 * diff.y;
			}
			p = p + 2 * fabs(diff.x);
			i++;
		}
	}
}

void	draw_line(t_2d p1, t_2d p2, t_data *data)
{
	int		dir;
	int		condition;
	t_2d	diff;
	t_2d	p3;

	p3 = p1;
	condition = fabs(p2.x - p1.x) > fabs(p2.y - p1.y);
	if ((p1.x > p2.x && condition) || (p1.y > p2.y && !condition))
	{
		p1 = p2;
		p2 = p3;
	}
	p1.color = round((p1.color + p2.color) / 2);
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if ((diff.y < 0 && condition) || (diff.x < 0 && !condition))
		dir = -1;
	if (condition)
		draw_line_h(p1, data, diff, dir);
	else
		draw_line_v(p1, data, diff, dir);
}
