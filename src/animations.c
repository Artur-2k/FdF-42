/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:33 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:34:01 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// this function will get called repeatedly very fast so
//we need to reduce the ammount of times it triggers color
// blink frequency (lower = less frequent)
static int	blinking_animation(t_data *data)
{
	int	blink_chance;
	int	i;
	int	j;

	blink_chance = 3;
	if (data->is_blinking)
	{
		i = 0;
		while (i < data->rows)
		{
			j = 0;
			while (j < data->cols)
			{
				if (data->matrix[i][j].z != 0 && rand() % 100 < blink_chance)
					data->matrix[i][j].color = rand() % 0x1000000;
				j++;
			}
			i++;
		}
	}
	return (0);
}

int	animation(t_data *data)
{
	if (data->is_blinking)
		blinking_animation(data);
	if (data->is_rotating)
	{
		data->alpha += 0.15;
		data->beta += 0.15;
		data->gama += 0.1;
		reset_projections_set_zoom(data);
		rotate_x(data, deg_to_rad(normalize_angle(data->alpha)));
		rotate_y(data, deg_to_rad(normalize_angle(data->beta)));
		rotate_z(data, deg_to_rad(normalize_angle(data->gama)));
		get_bounderies(data);
		get_offsets(data);
		translate(data, data->xoffset + data->xtranslate, \
					data->yoffset + data->ytranslate);
	}
	if (data->is_blinking || data->is_rotating)
		update_img(data);
	return (0);
}
