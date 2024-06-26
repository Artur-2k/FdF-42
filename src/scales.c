/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scales.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:06 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/26 17:47:17 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	manual_scale(t_data *data, int key)
{
	if (key == XK_t)
		data->scale += 0.5;
	else
	{
		if (data->scale > 1)
			data->scale -= 0.5;
	}

	reset_projections_set_zoom(data); // resets xyz_proj to xyz and applies scale

	// re-rotate
	rotate_x(data,DEG_TO_RAD( NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->beta) ));
	rotate_z(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->gama)) );

	// update offsets
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data); //center the map with the same offsets

	//* shitft the object offset + translation(if added any)
	translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}

void	manual_zscale(t_data *data, int key)
{
	if (key == XK_z)
		data->zscale++;
	else
		data->zscale--;

	reset_projections_set_zoom(data); // resets xyz_proj to xyz and applies scale

	// re-rotate
	rotate_x(data,DEG_TO_RAD( NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->beta) ));
	rotate_z(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->gama)) );

	// update offsets
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data); //center the map with the same offsets

	//* shitft the object offset + translation(if added any)
	translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}

// we check how much we need to zoom in based on the window and map lenght and width
// we choose the smaller scale so the whole map fits
static double	get_scale_factor(t_data *data)
{
	double	scale_x;
	double	scale_y;
	double	scale_factor;

	scale_x = WIN_LENGTH / abs(data->cols);
	scale_y = WIN_HEIGTH / abs(data->rows);
	scale_factor = get_min(scale_x, scale_y);
	if (scale_factor < 4) // optional
		return (1);
	return (scale_factor / 1.5); // can zoom more or less based on what we divided by
}

void	get_zoom(t_data *data)
{
	int i;
	int j;

	if (!data->scale) // if we dont have a scale we fetch one
		data->scale = get_scale_factor(data);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			data->matrix[i][j].proj_x *= data->scale;
			data->matrix[i][j].proj_y *= data->scale;
			data->matrix[i][j].proj_z *= data->zscale;
			j++;
		}
		i++;
	}
}