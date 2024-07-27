/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scales.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:06 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:12:01 by artuda-s         ###   ########.fr       */
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
	reset_projections_set_zoom(data);
	rotate_x(data, deg_to_rad(normalize_angle(data->alpha)));
	rotate_y(data, deg_to_rad(normalize_angle(data->beta)));
	rotate_z(data, deg_to_rad(normalize_angle(data->gama)));
	get_bounderies(data);
	get_offsets(data);
	translate(data, data->xoffset + data->xtranslate, \
				data->yoffset + data->ytranslate);
	update_img(data);
}

void	manual_zscale(t_data *data, int key)
{
	if (key == XK_z)
		data->zscale++;
	else
		data->zscale--;
	reset_projections_set_zoom(data);
	rotate_x(data, deg_to_rad(normalize_angle(data->alpha)));
	rotate_y(data, deg_to_rad(normalize_angle(data->beta)));
	rotate_z(data, deg_to_rad(normalize_angle(data->gama)));
	get_bounderies(data);
	get_offsets(data);
	translate(data, data->xoffset + data->xtranslate, \
				data->yoffset + data->ytranslate);
	update_img(data);
}

// we check how much we need to zoom in based on the window
// and map lenght and width
// we choose the smaller scale so the whole map fits
static double	get_scale_factor(t_data *data)
{
	double	scale_x;
	double	scale_y;
	double	scale_factor;

	scale_x = WIN_LENGTH / abs(data->cols);
	scale_y = WIN_HEIGTH / abs(data->rows);
	scale_factor = get_min(scale_x, scale_y);
	if (scale_factor < 4)
		return (1);
	return (scale_factor / 1.5);
}

void	get_zoom(t_data *data)
{
	int	i;
	int	j;

	if (!data->scale)
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
