/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:07:21 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/09 19:16:28 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>
# include "mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define RADIUS 0.523599
# define WIDTH 900
# define HEIGHT 600

typedef struct s_2d
{
	double	x;
	double	y;
}	t_2d;

typedef struct s_map
{
	int		width;
	int		height;
	t_2d	**matrix;
	double	max_x;
	double	max_y;
	double	min_x;
	double	min_y;
}	t_map;

typedef struct s_data
{
	void	*init;
	void	*display;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	sx;
	double	sy;
	double	offset_x;
	double	offset_y;
}	t_data;

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd, char **str);
int		ft_printf(const char *fstring, ...);
int		fill_map(char *argv, t_map *map);
t_2d	ft_transformation(int x, int y, int z);
void	free_all(t_2d ***matrix);
void	find_min(t_map *map, t_2d value);
#endif
