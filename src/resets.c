/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:02 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/26 18:43:56 by artuda-s         ###   ########.fr       */
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

	//  reseting color and xyz projections
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->matrix[i][j].color = data->matrix[i][j].restore_color; // restore point for color
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

	// reseting prespective and map controls
	reset_points(data); // resets the map projection and colors
	get_zoom(data); // fetches again the zoom factor

	//re rotates
		/*
		#define DEG_TO_RAD(deg) (deg * M_PI / 180)
		#define NORMALIZE_ANGLE(angle) (fmod(angle, 360.0))
		*/
	rotate_x(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->beta)));
	rotate_z(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->gama)));

	// update offsets
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data); //center the map with the same offsets

	//* shitft the object offset
	translate(data, data->xoffset, data->yoffset);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}
