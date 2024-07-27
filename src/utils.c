/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:08 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:09:31 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// returns the greater parameter
int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

// return the lesser parameter
int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

// function to open a file and check if it went wrong.
// returns the file descriptor
int	open_file(char *map_name, t_data *data)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		handle_error(OPEN_ERROR, data);
	return (fd);
}

// function to applie a random color if there isn't a z value
void	rand_colors(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (data->matrix[i][j].z != 0)
				data->matrix[i][j].color = rand() % 0x1000000;
			j++;
		}
		i++;
	}
	update_img(data);
}
