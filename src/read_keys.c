/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:14:27 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_keys(int key, t_data *data)
{
	if (key == XK_h || key == XK_j || key == XK_k || key == XK_l)
		manual_translation(data, key);
	else if (key == XK_w || key == XK_s || key == XK_a || key == XK_d
		|| key == XK_q || key == XK_e)
		manual_rotate(data, key);
	else if (key == XK_Escape) // esc
		exit_fdf(data);
	else if (key == XK_t || key == XK_y)
		manual_scale(data, key);
	else if (key == XK_z || key == XK_x)
		manual_zscale(data, key);
	else if (key == XK_c)
		rand_colors(data);
	else if (key == XK_Return) // enter
		restart(data);
	else if (key == XK_1 || key == XK_2)
		put_prespective(data, key);
	else if (key == XK_r)
		data->is_rotating = !data->is_rotating;
	else if (key == XK_b)
		data->is_blinking = !data->is_blinking;
	else
		return (1); //Error 1 2 3
	return (0); //success 0
}
