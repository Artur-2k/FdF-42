/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:33 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 21:01:17 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	blinking_animation(t_data *data)
{
	int	blink_chance;
	int	i;
	int	j;

	blink_chance = 3;
		// Adjust for desired blink frequency (lower = less frequent)
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
		reset_projections_set_zoom(data); //! resets xyz_proj to xyz back again
		//* step three re-rotate
		rotate_x(data, fmod((data->alpha), 360) * M_PI / 180);
		rotate_z(data, fmod((data->gama), 360) * M_PI / 180);
		rotate_y(data, fmod((data->beta), 360) * M_PI / 180);
		//* step pre-four if needed (on rotations) update map limits for offset
		get_bounderies(data); // makes it rotate on itself on not on the 0.0
		//* step four center the map with the same offsets
		get_offsets(data);
		//* shitft the object offset + translation(if added any)
		translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);
	}
	//* updates the image (could just 0 the memory of the image instead too)
	if (data->is_blinking || data->is_rotating)
		update_img(data);
	return (0);
}
