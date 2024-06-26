/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:33 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/25 02:46:20 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	blinking_animation(t_data *data)
{
	int	blink_chance;
	int	i;
	int	j;

	// this function will get called repeatedly very fast so 
	//we need to reduce the ammount of times it triggers color
	// blink frequency (lower = less frequent) 
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
}

int	animation(t_data *data)
{
	// if blinking key was pressed
	if (data->is_blinking)
		blinking_animation(data);
	// if rotating key was pressed
	if (data->is_rotating) 
	{
		data->alpha += 0.15;
		data->beta += 0.15;
		data->gama += 0.1;
		
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
	}
	//* updates the image (could just 0 the memory of the image instead too)
	if (data->is_blinking || data->is_rotating)
		update_img(data);
	return (0);
}
