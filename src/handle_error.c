/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:50 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:10:23 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int errnum, t_data *data)
{
	if (errnum == -1) // malloc error
	{
		ft_putstr_fd("A malloc error occured\nTerminating!\n", 2);
		exit_fdf(data);
	}
	else if (errnum == -2) // read error
	{
		ft_putstr_fd("A read error occured\nTerminating!\n", 2);
		exit_fdf(data);
	}
	else if (errnum == -3) // OPEN_ERROR
	{
		ft_putstr_fd("Error opening the file\nTerminating!\n", 2);
		exit_fdf(data);
	}
	else // MLX_ERROR
	{
		ft_putstr_fd("A MLX related error occured\nTerminating!\n", 2);
		exit_fdf(data);
	}
}
