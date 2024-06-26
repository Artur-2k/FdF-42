read the map and store it into a 2d matrix that stores points coordinates and color
	mallocs for 2d arrays
	get_next_line
		open
		read
		close
	retriving the specific data for each data of the point

inicialize the mlx stuff
	mlx_init
	mlx_new_window
	mlx_new_image
	mlx_loop

start the map
	get the appropriete scale
	rotate the pixel coordinates on x,y,z
		matrix rotations
	find map bounderies and set the map to the middle of the window
	draw the map connecting every vertex to the right and down (execept last ones)
		pixel to image (find memory offset for coloring pixels)
		bresenhams line algorithm
		mlx_put_image_to_window

read inpus
	key_hooks
		define keybindings
		for rotation
			+/- angle for key press
			matrix_rotations
			euler (gimbal lock) for rotation axis parenting (x->z->y)
			map_update
				destroy image and create a new one (could also bzero everything probably more efficient);
		for translation
			+/- shift on x/y for key press
			map_update
	mouse_hooks





https://www.youtube.com/watch?v=zc8b2Jo7mno

Euler (gimball lock)



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:04 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/25 02:39:37 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

	void	rotate_x(t_data *data, double alpha)
	{
		int	tmp_y;
		int	i;
		int	j;

		i = 0;
		while (i < data->rows)
		{
			j = 0;
			while (j < data->cols)
			{
				tmp_y = data->matrix[i][j].proj_y;
				data->matrix[i][j].proj_y = (int)(tmp_y * cos(alpha) - data->matrix[i][j].proj_z * sin(alpha));
				data->matrix[i][j].proj_z = (int)(tmp_y * sin(alpha) + data->matrix[i][j].proj_z * cos(alpha));
				j++;
			}
			i++;
		}
	}

	void	rotate_y(t_data *data, double beta)
	{
		int	tmp_x;
		int tem_y;
		int	i;
		int	j;

		i = 0;
		while (i < data->rows)
		{
			j = 0;
			while (j < data->cols)
			{
				tmp_x = data->matrix[i][j].proj_x;
				tem_y = data->matrix[i][j].proj_y;
				data->matrix[i][j].proj_x = (int)(tmp_x * cos(beta)	+ data->matrix[i][j].proj_z * sin(beta));
				data->matrix[i][j].proj_z = (int)(-tmp_x * sin(beta) + data->matrix[i][j].proj_z * cos(beta));
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

		i = 0;
		while (i < data->rows)
		{
			j = 0;
			while (j < data->cols)
			{
				tmp_x = data->matrix[i][j].proj_x;
				data->matrix[i][j].proj_x = (int)(tmp_x * cos(gama) - data->matrix[i][j].proj_y * sin(gama));
				data->matrix[i][j].proj_y = (int)(tmp_x * sin(gama) + data->matrix[i][j].proj_y * cos(gama));
				j++;
			}
			i++;
		}
	}

void	manual_rotate(t_data *data, int key)
{
    if (key == XK_w)
        data->alpha = fmin(data->alpha + ANGLE_CHANGE, 90);
    else if (key == XK_s)
        data->alpha = fmax(data->alpha - ANGLE_CHANGE, -90);
    else if (key == XK_d)
        data->beta = fmin(data->beta + ANGLE_CHANGE, 90);
    else if (key == XK_a)
        data->beta = fmax(data->beta - ANGLE_CHANGE, -90);
    else if (key == XK_q)
        data->gama = fmin(data->gama + ANGLE_CHANGE, 90);
    else if (key == XK_e)
        data->gama = fmax(data->gama - ANGLE_CHANGE, -90);

	reset_projections_set_zoom(data); //! resets xyz_proj to xyz back again
	rotate_x(data,DEG_TO_RAD( NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->beta) ));
	rotate_z(data,DEG_TO_RAD (NORMALIZE_ANGLE(data->gama)) );
	get_bounderies(data); // makes it rotate on itself on not on the 0.0
	get_offsets(data);
	translate(data, data->xoffset + data->xtranslate, data->yoffset + data->ytranslate);
	update_img(data);
}

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
	//* resets xyz_proj to xyz back again
	reset_projections_set_zoom(data);

	//* step three re-rotate
	rotate_x(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->alpha)));
	rotate_y(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->beta)));
	rotate_z(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->gama)));

	//* step pre-four if needed (on rotations) update map limits for offset
	get_bounderies(data); // makes it rotate on itself on not on the 0.0

	//* step four center the map with the same offsets
	get_offsets(data);

	//* shitft the object offset + translation(if added any)
	translate(data, data->xoffset + data->xtranslate, data->yoffset
			+ data->ytranslate);

	//* updates the image (could just 0 the memory of the image instead too)
	update_img(data);
}

