/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:47 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/30 17:20:11 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_h(t_3d p1, t_3d p2, t_data *data)

{
	int		dir;
	int		p;
	int		y;
	int		i;
	t_2d	diff;
	t_3d	p3;

	i = 0;
	p3 = p1;
	p = 0;
	y = 0;
	if (p1.x > p2.x)
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if (diff.y < 0)
		dir = -1;
	if (diff.x != 0)
	{
		y = p1.y;
		p = 2*diff.y - diff.x;
		while (i < diff.x)
		{
			my_mlx_pixel_put(data, p1.x + i, y, p1.color);
			if (p > 0)
			{
				y += dir;
				p -= 2*fabs(diff.x);
			}
			p += 2*fabs(diff.y);
			i++;
		}
	}
}

void	draw_line_v(t_3d p1, t_3d p2, t_data *data)
{
	int		dir;
	int		p;
	int		x;
	int		i;
	t_3d	diff;
	t_3d	p3;

	p3 = p1;
	p = 0;
	x = 0;
	i = 0;
	if (p1.y > p2.y)
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = (p2.x - p1.x);
	diff.y = (p2.y - p1.y);
	dir = 1;
	if (diff.x < 0)
		dir = -1;
	if (diff.x > 0 && diff.y > 0)
		p1.color = p2.color;
	if (diff.x != 0)
	{
		x = p1.x;
		p = 2*diff.x - diff.y;
		while (i < diff.y)
		{
			my_mlx_pixel_put(data, x, p1.y + i, p1.color);
			if (p > 0)
			{
				x += dir;
				p = p - 2*fabs(diff.y);
			}
			p = p + 2*fabs(diff.x);
			i++;
		}
	}
}

void	draw_line(t_3d p1, t_3d p2, t_data *data)
{
	p2.color = p1.color;
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		draw_line_h(p1, p2, data);
	else
		draw_line_v(p1, p2, data);
}
