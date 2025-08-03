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

// A helper function to extract color components
int	get_rgb(int color, int scaler)
{
	return ((color >> scaler) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

// A helper function to create a new color from components
unsigned int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Function to interpolate a color
unsigned int	interpolate_color(int color1, int color2, double t)
{
	int r1 = get_rgb(color1, 16);
	int g1 = get_rgb(color1, 8);
	int b1 = get_rgb(color1, 0);

	int r2 = get_rgb(color2, 16);
	int g2 = get_rgb(color2, 8);
	int b2 = get_rgb(color2, 0);

	int r_interp = r1 + (r2 - r1) * t;
	int g_interp = g1 + (g2 - g1) * t;
	int b_interp = b1 + (b2 - b1) * t;

	return (create_rgb(r_interp, g_interp, b_interp));
}

void	draw_line_h(t_3d p1, t_3d p2, t_data *data)

{
	int		dir;
	int		p;
	int		y;
	int		i;
	t_2d	diff;
	t_3d	p3;
	double t;
	unsigned int color;


	i = 0;
	p3 = p1;
	p = 0;
	y = 0;
	if (p1.x > p2.x)
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = fabs(p2.x - p1.x);
	diff.y = p2.y - p1.y;
	dir = 1;
	if (diff.y < 0)
		dir = -1;
	if (diff.x != 0)
	{
		y = p1.y;
		p = 2*diff.y - diff.x;
		while (i < fabs(diff.x))
		{
			t = (double)i / (double)diff.x;
			color = interpolate_color(p1.color, p2.color, t);
			my_mlx_pixel_put(data, p1.x + i, y, color);
			if (p > 0)
			{
				y += dir;
				p -= 2*diff.x;
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
	double	t;
	int	color;

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
	diff.y = fabs(p2.y - p1.y);
	dir = 1;
	if (diff.x < 0)
		dir = -1;
	if (diff.x != 0)
	{
		x = p1.x;
		p = 2*diff.x - diff.y;
		while (i < diff.y)
		{
			t = (double)i / (double)diff.y;
			color = interpolate_color(p1.color, p2.color, t);
			my_mlx_pixel_put(data, x, p1.y + i, color);
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

int	is_over_limit(t_3d p)
{
	if (fabs(p.x) > WIDTH && fabs(p.y) > HEIGHT)
		return (1);
	return (0);
}

void	draw_line(t_3d p1, t_3d p2, t_data *data)
{
	if (is_over_limit(p1) && is_over_limit(p2))
		return ;
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		draw_line_h(p1, p2, data);
	else
		draw_line_v(p1, p2, data);
}
