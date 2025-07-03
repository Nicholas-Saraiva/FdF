/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/02 14:18:32 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_matrix	*map;

	map = malloc(sizeof(t_matrix));
	map -> width = 0;
	map -> height = 0;
	map -> matrix = 0;
	if (!fill_map(argv[argc - 1], map))
		return (0);
	data.init = mlx_init();
	if (!data.init)
		return (1);
	data.display = mlx_new_window(data.init, 900, 600, "FdF");

	mlx_destroy_window(data.init, data.display);
	mlx_destroy_display(data.init);
	free(data.init);
	return (0);
}
