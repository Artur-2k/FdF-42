/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:09 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 19:52:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_data *data, int x_shift_value, int y_shift_value)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (x_shift_value)
				data->matrix[i][j].proj_x += x_shift_value;
			if (y_shift_value)
				data->matrix[i][j].proj_y += y_shift_value;
			j++;
		}
		i++;
	}
}

void	manual_translation(t_data *data, int key)
{
	if (key == XK_j)
	{
		data->ytranslate -= SHIFT_VALUE;
		translate(data, 0, -SHIFT_VALUE);
	}
	else if (key == XK_k)
	{
		data->ytranslate += SHIFT_VALUE;
		translate(data, 0, SHIFT_VALUE);
	}
	else if (key == XK_l)
	{
		data->xtranslate += SHIFT_VALUE;
		translate(data, SHIFT_VALUE, 0);
	}
	else if (key == XK_h)
	{
		data->xtranslate -= SHIFT_VALUE;
		translate(data, -SHIFT_VALUE, 0);
	}
	update_img(data);
}
