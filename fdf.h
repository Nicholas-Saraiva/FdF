# ifndef FDF_H
#define FDF_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"

typedef struct s_win
{
    void    *init;
	void	*display;
}	t_data;

typedef struct s_2d {
	double	x;
	double	y;
}	t_2d;

typedef struct s_3d {
	double	x;
	double	y;
	double	z;
}	t_3d;

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		ft_printf(const char *fstring, ...);
int		check_map(int fd);
#endif
