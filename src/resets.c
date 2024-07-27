/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:02 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:18:42 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// resets the projection to the original map and applies the scale
void	reset_projections_set_zoom(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->matrix[i][j].proj_x = data->matrix[i][j].x * data->scale;
			data->matrix[i][j].proj_y = data->matrix[i][j].y * data->scale;
			data->matrix[i][j].proj_z = data->matrix[i][j].z * data->zscale;
			j++;
		}
		i++;
	}
}

// resets the projection to the original map and restores its colors
static void	reset_points(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->matrix[i][j].color = data->matrix[i][j].restore_color;
			data->matrix[i][j].proj_x = data->matrix[i][j].x;
			data->matrix[i][j].proj_y = data->matrix[i][j].y;
			data->matrix[i][j].proj_z = data->matrix[i][j].z;
			j++;
		}
		i++;
	}
}

void	restart(t_data *data)
{
	data->is_blinking = 0;
	data->is_rotating = 0;
	data->zscale = 1;
	data->scale = 0;
	data->alpha = 45;
	data->beta = -35;
	data->gama = 30;
	data->xtranslate = 0;
	data->ytranslate = 0;
	reset_points(data);
	get_zoom(data);
	rotate_x(data, deg_to_rad(normalize_angle(data->alpha)));
	rotate_y(data, deg_to_rad(normalize_angle(data->beta)));
	rotate_z(data, deg_to_rad(normalize_angle(data->gama)));
	get_bounderies(data);
	get_offsets(data);
	translate(data, data->xoffset, data->yoffset);
	update_img(data);
}
