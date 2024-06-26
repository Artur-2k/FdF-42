/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_boundaries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:44 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:51:14 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to get the limits of my map projection.
void	get_bounderies(t_data *data)
{
	int	i;
	int	j;

	data->boundaries.maxx = data->matrix[0][0].proj_x;
	data->boundaries.maxy = data->matrix[0][0].proj_y;
	data->boundaries.minx = data->matrix[0][0].proj_x;
	data->boundaries.miny = data->matrix[0][0].proj_y;
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->boundaries.maxx = get_max(data->boundaries.maxx, data->matrix[i][j].proj_x);
			data->boundaries.maxy = get_max(data->boundaries.maxy, data->matrix[i][j].proj_y);
			data->boundaries.minx = get_min(data->boundaries.minx, data->matrix[i][j].proj_x);
			data->boundaries.miny = get_min(data->boundaries.miny, data->matrix[i][j].proj_y);
			j++;
		}
		i++;
	}
}
