/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:10:45 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/26 17:41:06 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


// destroys the old image and creates a new one
// maybe would be better to bzero the pixels but now its done xd
// redraws the map with the projections.
void	update_img(t_data *data)
{
	if (data->img.img_ptr && data->mlx_win)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		new_image(data);
	}
	draw_map(data);
}

// creates a new image
void	new_image(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_LENGTH, WIN_HEIGTH);
	if (!data->img.img_ptr)
		handle_error(MLX_ERROR, data);
	data->img.img_addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.img_addr)
		handle_error(MLX_ERROR, data);
}
