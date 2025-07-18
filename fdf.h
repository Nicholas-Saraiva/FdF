/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:07:21 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/18 15:55:09 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>
# include <stdio.h>
# include "mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define RADIUS 0.523599
# define WIDTH 1400
# define HEIGHT 800
# define KEY_A 97
# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define COLOR 0xFFEFC8

typedef struct s_2d
{
	double	x;
	double	y;
}	t_2d;

typedef struct s_3d
{
	double	x;
	double	y;
	double	z;
}	t_3d;

typedef struct s_map
{
	int		width;
	int		height;
	t_3d	**matrix;
	t_3d	center;
	double	max_x;
	double	max_y;
	double	min_x;
	double	min_y;
}	t_map;

typedef struct s_data
{
	t_map	*map;
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
t_2d	ft_transformation(t_3d matrix1d);
void	free_map(t_map *map);
void	free_matrix(double ***matrix, const int dim);
void	find_min(t_map *map, t_3d value);
void	ft_error(const char *msg);
void	ft_rotateCenter(t_data *map, t_3d (*RotationFunc)(t_3d, double), double angle);
void	drawLine(t_2d p1, t_2d p2, t_data *data);
double	*ft_multMatrix3dto1d(double *leftMatrix[], double *rightMatrix);
double	**ft_multMatrix3d(double *leftMatrix[], double *rightMatrix[]);
double	**initMatrix();
t_3d	RotateX(t_3d matrix1d, const double angle);
t_3d	RotateY(t_3d matrix1d, const double angle);
t_3d	RotateZ(t_3d matrix1d, const double angle);
#endif
