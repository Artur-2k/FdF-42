/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:04 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/26 18:43:38 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_data *data, double alpha)
{
	int	tmp_y;
	int	i;
	int	j;
	double cos_alpha;
	double sin_alpha;

	sin_alpha = sin(alpha);
	cos_alpha = cos(alpha);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_y = data->matrix[i][j].proj_y;
			data->matrix[i][j].proj_y = (int)(tmp_y * cos_alpha - data->matrix[i][j].proj_z * sin_alpha);
			data->matrix[i][j].proj_z = (int)(tmp_y * sin_alpha + data->matrix[i][j].proj_z * cos_alpha);
			j++;
		}
		i++;
	}
}

void	rotate_y(t_data *data, double beta)
{
	int	tmp_x;
	int	i;
	int	j;
	double cos_beta;
	double sin_beta;

	sin_beta = sin(beta);
	cos_beta = cos(beta);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_x = data->matrix[i][j].proj_x;
			data->matrix[i][j].proj_x = (int)(tmp_x * cos_beta	+ data->matrix[i][j].proj_z * sin_beta);
			data->matrix[i][j].proj_z = (int)(-tmp_x * sin_beta + data->matrix[i][j].proj_z * cos_beta);
			j++;
		}
		i++;
	}
}

void	rotate_z(t_data *data, double gama)
{
	int	tmp_x;
	int	i;
	int	j;
	double cos_gama;
	double sin_gama;

	sin_gama = sin(gama);
	cos_gama = cos(gama);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			tmp_x = data->matrix[i][j].proj_x;
			data->matrix[i][j].proj_x = (int)(tmp_x * cos_gama - data->matrix[i][j].proj_y * sin_gama);
			data->matrix[i][j].proj_y = (int)(tmp_x * sin_gama + data->matrix[i][j].proj_y * cos_gama);
			j++;
		}
		i++;
	}
}

void	manual_rotate(t_data *data, int key)
{
	// each respective key press changes the angle accordingly
    if (key == XK_w)
        data->alpha +=  ANGLE_CHANGE;
    else if (key == XK_s)
        data->alpha -=  ANGLE_CHANGE;
    else if (key == XK_d)
        data->beta +=  ANGLE_CHANGE;
    else if (key == XK_a)
        data->beta -=  ANGLE_CHANGE;
    else if (key == XK_q)
        data->gama +=  ANGLE_CHANGE;
    else if (key == XK_e)
        data->gama -=  ANGLE_CHANGE;

//! IMPORTANT INFORMATION ON WHY WE CAN'T ALWAYS USE FUNCTION CALLS !//
/* Sequence Points: C and C++ defines specific points in the code
 execution where the order of operations is guaranteed to be
  deterministic. These points typically occur at the end of statements
  (e.g., after a semicolon).
Indeterminacy Between Sequence Points: In the absence of sequence
 points, the compiler has freedom to rearrange calculations within a
  function. This includes function calls, as long as the final outcome
  remains functionally equivalent.
 Impact on Output: The difference in output might be negligible in many
  cases. However, for calculations involving floating-point numbers and
  rounding errors, the reordering within a function call might be different
  from the specific order you write in the the previous, leading to
  slight variations.
*/


	reset_projections_set_zoom(data); // resets xyz_proj to xyz and applies scale
	// re-rotate
		/*
		#define DEG_TO_RAD(deg) (deg * M_PI / 180)
		#define NORMALIZE_ANGLE(angle) (fmod(angle, 360.0))
		*/
	rotate_x(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->beta)));
	rotate_z(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->gama)));

	// update offsets
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data); //center the map with the same offsets

	//* shitft the object offset + translation(if added any)
	translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}

// change the angles for each prespective and redraw de map with the new projections
void	put_prespective(t_data *data, int key)
{
	if (key == XK_1)
	{
		//top view
		data->alpha = 0;
		data->beta = 0;
		data->gama = 0;
	}
	else
	{
		//paralel view
		data->alpha = 90;
		data->beta = 0;
		data->gama = 0;
	}

	reset_projections_set_zoom(data); // resets xyz_proj to xyz and applies scale
	// re-rotate
		/*
		#define DEG_TO_RAD(deg) (deg * M_PI / 180)
		#define NORMALIZE_ANGLE(angle) (fmod(angle, 360.0))
		*/
	rotate_x(data,DEG_TO_RAD( NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->beta)));
	rotate_z(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->gama)));

	// update offsets
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data); //center the map with the same offsets

	//* shitft the object offset + translation(if added any)
	translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}