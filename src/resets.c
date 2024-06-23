/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:02 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 21:19:11 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void	reset_points(t_data *data)
{
	int	i;
	int	j;

	//  reseting color and xyz projections
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
	reset_points(data);
	// reseting animation
	data->is_blinking = 0;
	data->is_rotating = 0;
	// reseting scales
	data->zscale = 1;
	data->scale = 0;
	// reseting rotation to isometric
	data->alpha = 45;
	data->beta = -35;
	data->gama = 30;
	//reseting translation
	data->xtranslate = 0;
	data->ytranslate = 0;
	// reseting prespective and map control
	get_zoom(data);
	rotate_x(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->alpha)));
	rotate_z(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->gama)));
	rotate_y(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->beta)));
	get_bounderies(data);
	get_offsets(data);
	translate(data, data->xoffset, data->yoffset);
	draw_map(data);
	update_img(data);
}
