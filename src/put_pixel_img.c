/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:57 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/26 18:18:11 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// dst => the address of the pixels in memory
// we adjust the offset of the with our x,y coords of the pixel along with the
// line_len and the bpp and just apply to that pixel the respective color
void	put_pixel_to_img(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIN_LENGTH && y < WIN_HEIGTH)
	{
		dst = img.img_addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}
