/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:07:21 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/05 18:30:07 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH 1400
# define HEIGHT 800
# define KEY_A 97
# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_Q 113
# define KEY_E 101
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define COLOR 0x3f6d4e
# define G_COLOR 0x00ff9f
# define P_COLOR 0xbd00ff
# define FLT_MAX 1E+37
# define FLT_MIN -1E+37

typedef struct s_2d
{
	float			x;
	float			y;
	unsigned int	color;
}	t_2d;

typedef struct s_3d
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}	t_3d;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_line
{
	t_3d	diff;
	float	dz;
	int		p;
	int		i;
}	t_line;

typedef struct s_rotation
{
	float	x;
	float	y;
	float	z;
}	t_rotation;

typedef struct s_map
{
	int			width;
	int			height;
	t_3d		**matrix;
	t_3d		**matrix_cpy;
	t_3d		center;
	t_3d		(*projection)(t_3d);
	t_rotation	rotation;
	float		max_x;
	float		max_y;
	float		min_x;
	float		min_y;
	float		sx;
	float		sy;
	float		offset_x;
	float		offset_y;
	float		zoom;
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
	float	*zbuffer;
}	t_data;

//------Maps
int				get_width(char *argv);
int				get_height(char *argv);
int				fill_map(char *argv, t_map *map);
void			draw_line(t_3d p1, t_3d p2, t_data *data);
unsigned int	get_color(t_3d point, char *split);
unsigned int	interpolate_color(int color1, int color2,
					int step, float steps);

//-----Render
void			display_image(t_map *map, t_data *data);
void			my_mlx_pixel_put(t_data *data, t_3d point);

//-----Hooks
int				key_up(int keycode, t_data *data);
int				key_down(int keycode, t_data *data);
int				mouse_hook(int keycode, int x, int y, t_data *data);
void			ft_hooks(t_data *data);

//-----Math
t_3d			ft_apply_rotation(t_map *map, t_3d point3d, float angle,
					t_3d (*rotate)(t_3d, float));
t_3d			rotate_x(t_3d matrix1d, float r);
t_3d			rotate_y(t_3d matrix1d, float r);
t_3d			rotate_z(t_3d matrix1d, float r);
t_3d			sum_3d_points(t_3d point1, t_3d point2);
t_3d			subtrate_3d_points(t_3d point1, t_3d point2);
t_3d			ft_isometric(t_3d matrix1d);
t_3d			new_point3d(int x, int y, int z);
t_3d			ft_plane(t_3d matrix1d);
unsigned int	ft_atoi_base(const char *nptr, int base);

//-----Errors
void			ft_error_map(const char *msg, t_map *map);
void			ft_error_data(const char *msg, t_data *data);

//-----Utils
int				free_map(t_map *map);
int				free_data(t_data *data);
void			find_limits(t_map *map, t_3d value);
void			free_matrix_3d(t_3d **matrix, t_map *map);
t_3d			**ft_matrix_cpy(t_map *map, t_3d **matrix);

//-----Includes
char			**ft_split(char const *s, char c);
char			*get_next_line(int fd, char **str);
#endif
