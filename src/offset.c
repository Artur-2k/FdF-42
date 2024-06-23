/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:59 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 21:29:44 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_offsets(t_data *data)
{
    int width;
    int height;

    width = abs(data->boundaries.maxx - data->boundaries.minx);
    height = abs(data->boundaries.maxy - data->boundaries.miny);
    data->xoffset = round((WIN_LENGTH - width) / 2.0);
    data->yoffset = round((WIN_HEIGTH - height) / 2.0);
    if (data->boundaries.minx < 0)
        data->xoffset += abs((int)round(data->boundaries.minx));
    if (data->boundaries.miny < 0)
        data->yoffset += abs((int)round(data->boundaries.miny));
	return (0);
}

