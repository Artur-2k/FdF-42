/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:35 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:06:27 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	bresenham_part2(t_data *data, t_point A, t_point B, t_bsnh bsnh);

// bresenham's line drawing algorithm. wikipedia page is acctually good for
// a better understanding
// fun fact. because i initiallized no color from map to -1,
// it goes to the max color (white 0xFFFFFF)
// and if i put 0x1000000 it would go back to black
void	bresenham_part1(t_data *data, t_point A, t_point B)
{
	t_bsnh	bsnh;

	bsnh.dx = abs(B.proj_x - A.proj_x);
	if (A.proj_x < B.proj_x)
		bsnh.sx = 1;
	else
		bsnh.sx = -1;
	bsnh.dy = -abs(B.proj_y - A.proj_y);
	if (A.proj_y < B.proj_y)
		bsnh.sy = 1;
	else
		bsnh.sy = -1;
	bsnh.error = bsnh.dx + bsnh.dy;
	bresenham_part2(data, A, B, bsnh);
}

static void	bresenham_part2(t_data *data, t_point A, t_point B, t_bsnh bsnh)
{
	while (1)
	{
		put_pixel_to_img(data->img, A.proj_x, A.proj_y, get_max(A.color, \
						B.color));
		if (A.proj_x == B.proj_x && A.proj_y == B.proj_y)
			break ;
		bsnh.e2 = 2 * bsnh.error;
		if (bsnh.e2 >= bsnh.dy)
		{
			if (A.proj_x == B.proj_x)
				break ;
			bsnh.error = bsnh.error + bsnh.dy;
			A.proj_x += bsnh.sx;
		}
		if (bsnh.e2 <= bsnh.dx)
		{
			if (A.proj_y == B.proj_y)
				break ;
			bsnh.error = bsnh.error + bsnh.dx;
			A.proj_y += bsnh.sy;
		}
	}
}

// connecting every matrix element to its next to the right and
// next down bellow until we reach oneof the limits or both at
//the end using the bresenham algorithm
void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (j < data->cols - 1)
				bresenham_part1(data, data->matrix[i][j], \
								data->matrix[i][j + 1]);
			if (j > 0)
				bresenham_part1(data, data->matrix[i][j], \
								data->matrix[i][j - 1]);
			if (i < data->rows - 1)
				bresenham_part1(data, data->matrix[i][j], \
								data->matrix[i + 1][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img_ptr, 0,
		0);
}
