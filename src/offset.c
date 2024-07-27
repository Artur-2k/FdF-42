/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:59 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:20:08 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// get the map lenght and height and the difference of the window and
//map dimensions diveded by two (to center at 50%) will be our offset
// as rotation is made first we might have negative values on the map
//coordinates on the window so we just put the min to 0 (x and y if needed)
int	get_offsets(t_data *data)
{
	int	width;
	int	height;

	width = abs(data->boundaries.maxx - data->boundaries.minx);
	height = abs(data->boundaries.maxy - data->boundaries.miny);
	data->xoffset = round((WIN_LENGTH - width) / 2.0);
	data->yoffset = round((WIN_HEIGTH - height) / 2.0);
	if (data->boundaries.minx < 0)
		data->xoffset += abs((data->boundaries.minx));
	if (data->boundaries.miny < 0)
		data->yoffset += abs((data->boundaries.miny));
	return (0);
}
