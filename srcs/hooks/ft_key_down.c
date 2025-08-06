#include "fdf.h"

static void	ft_rotation_events(int keycode, t_data *data)
{
	if (keycode == 113)
		data->map->rotation.z =  0;
	if (keycode == 101)
		data->map->rotation.z =  0;
	if (keycode == 49)
		data->map->rotation.y = 0;
	if (keycode == 50)
		data->map->rotation.y = 0;
	if (keycode == 51)
		data->map->rotation.x = 0;
	if (keycode == 52)
		data->map->rotation.x = 0;
	printf("\n%f\n", data->map->rotation.y);
}

int	key_down(int keycode, t_data *data)
{
	static int	type;

	if (!type)
		type = 0;
	ft_rotation_events(keycode, data);
	return (0);
}
