# ifndef FDF_H
#define FDF_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_2d {
	double	x;
	double	y;
}	t_2d;

typedef struct s_3d {
	double	x;
	double	y;
	double	z;
}	t_3d;

typedef struct s_matrix {
	int	width;
	int	height;
	int	**matrix;
} t_matrix;

typedef struct s_data {
	void	*init;
	void	*display;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd, char **str);
int		ft_printf(const char *fstring, ...);
int		fill_map(char *argv, t_matrix *map);
#endif
