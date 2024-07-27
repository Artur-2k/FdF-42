/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:04 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:15:30 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_data *data, double alpha)
{
	int		tmp_y;
	int		i;
	int		j;
	double	cos_alpha;
	double	sin_alpha;

	sin_alpha = sin(alpha);
	cos_alpha = cos(alpha);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_y = data->matrix[i][j].proj_y;
			data->matrix[i][j].proj_y = (int)(tmp_y * cos_alpha \
						- data->matrix[i][j].proj_z * sin_alpha);
			data->matrix[i][j].proj_z = (int)(tmp_y * sin_alpha \
						+ data->matrix[i][j].proj_z * cos_alpha);
			j++;
		}
		i++;
	}
}

void	rotate_y(t_data *data, double beta)
{
	int		tmp_x;
	int		i;
	int		j;
	double	cos_beta;
	double	sin_beta;

	sin_beta = sin(beta);
	cos_beta = cos(beta);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_x = data->matrix[i][j].proj_x;
			data->matrix[i][j].proj_x = (int)(tmp_x * cos_beta \
							+ data->matrix[i][j].proj_z * sin_beta);
			data->matrix[i][j].proj_z = (int)(-tmp_x * sin_beta \
							+ data->matrix[i][j].proj_z * cos_beta);
			j++;
		}
		i++;
	}
}

void	rotate_z(t_data *data, double gama)
{
	int		tmp_x;
	int		i;
	int		j;
	double	cos_gama;
	double	sin_gama;

	sin_gama = sin(gama);
	cos_gama = cos(gama);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_x = data->matrix[i][j].proj_x;
			data->matrix[i][j].proj_x = (int)(tmp_x * cos_gama \
								- data->matrix[i][j].proj_y * sin_gama);
			data->matrix[i][j].proj_y = (int)(tmp_x * sin_gama \
								+ data->matrix[i][j].proj_y * cos_gama);
			j++;
		}
		i++;
	}
}

void	manual_rotate(t_data *data, int key)
{
	if (key == XK_w)
		data->alpha += ANGLE_CHANGE;
	else if (key == XK_s)
		data->alpha -= ANGLE_CHANGE;
	else if (key == XK_d)
		data->beta += ANGLE_CHANGE;
	else if (key == XK_a)
		data->beta -= ANGLE_CHANGE;
	else if (key == XK_q)
		data->gama += ANGLE_CHANGE;
	else if (key == XK_e)
		data->gama -= ANGLE_CHANGE;
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

// change the angles for each prespective and redraw de map
//with the new projections
void	put_prespective(t_data *data, int key)
{
	if (key == XK_1)
	{
		data->alpha = 0;
		data->beta = 0;
		data->gama = 0;
	}
	else
	{
		data->alpha = 90;
		data->beta = 0;
		data->gama = 0;
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
