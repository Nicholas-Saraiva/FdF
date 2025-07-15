/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:07:21 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/15 17:56:28 by nsaraiva         ###   ########.fr       */
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
t_2d	ft_transformation(int x, int y, int z);
void	free_map(t_map *map);
void	free_matrix(double ***matrix, const int dim);
void	find_min(t_map *map, t_2d value);
void	ft_error(const char *msg);
double	*ft_multMatrix3dto1d(double *leftMatrix[], double *rightMatrix);
double	**ft_multMatrix3d(double *leftMatrix[], double *rightMatrix[]);
double	**initMatrix();
#endif
