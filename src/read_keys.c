/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:28:31 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// will get the key pressed and the data address passed as a parameter
// a bunch of if else for each group of control commands that will trigger
//the respective control function
int	read_keys(int key, t_data *data)
{
	if (key == XK_h || key == XK_j || key == XK_k || key == XK_l)
		manual_translation(data, key);
	else if (key == XK_w || key == XK_s || key == XK_a || key == XK_d
		|| key == XK_q || key == XK_e)
		manual_rotate(data, key);
	else if (key == XK_Escape)
		exit_fdf(data);
	else if (key == XK_t || key == XK_y)
		manual_scale(data, key);
	else if (key == XK_z || key == XK_x)
		manual_zscale(data, key);
	else if (key == XK_c)
		rand_colors(data);
	else if (key == XK_Return)
		restart(data);
	else if (key == XK_1 || key == XK_2)
		put_prespective(data, key);
	else if (key == XK_r)
		data->is_rotating = !data->is_rotating;
	else if (key == XK_b)
		data->is_blinking = !data->is_blinking;
	else
		return (1);
	return (0);
}
