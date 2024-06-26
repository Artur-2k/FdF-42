/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:41 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 19:52:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to free the map matrix
void	free_matrix(t_point **matrix, int stopping_index)
{
	int	index;

	index = 0;
	while (index < stopping_index)
		free(matrix[index++]);
	free(matrix);
	return ;
}
