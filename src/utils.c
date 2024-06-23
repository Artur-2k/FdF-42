/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:35:08 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:20:58 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	open_file(char *map_name, t_data *data)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		handle_error(OPEN_ERROR, data);
	return (fd);
}

double	deg_to_rad(double deg)
{
	return ((deg) * M_PI / 180.0);
}

double	normalize_angle(double angle)
{
	return ((angle) = fmod((angle), 360));
}
