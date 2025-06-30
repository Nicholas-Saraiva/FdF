/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/30 19:21:05 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t ft_array_len(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	ft_free_all(char **str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_array_len(str);
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_map(int fd)
{
	char	*str;
	char	**first_row;
	char	**second_row;

	str = get_next_line(fd);
	if (!str)
		return (0);
	first_row = ft_split(str, ' ');
	if (!first_row)
	{
		free(str);
		return (0);
	}
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		second_row = ft_split(str, ' ');
		if (str && second_row < first_row)
			return (free(str), ft_free_all(first_row), ft_free_all(second_row), 0);
		ft_free_all(second_row);
	}
	return (free(str), ft_free_all(first_row), ft_free_all(second_row), 1);
}
