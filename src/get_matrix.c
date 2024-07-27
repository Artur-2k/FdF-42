/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:47 by artuda-s          #+#    #+#             */
/*   Updated: 2024/07/27 17:27:56 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	initialize_row(t_point ***matrix, int current_row, int cols)
{
	int	j;

	j = 0;
	while (j < cols)
	{
		(*matrix)[current_row][j].x = j;
		(*matrix)[current_row][j].y = current_row;
		(*matrix)[current_row][j].z = 0;
		(*matrix)[current_row][j].proj_x = j;
		(*matrix)[current_row][j].proj_y = current_row;
		(*matrix)[current_row][j].proj_z = 0;
		(*matrix)[current_row][j].color = -1;
		(*matrix)[current_row][j].restore_color = -1;
		j++;
	}
}

// allocation of memory for the 2D matrix
// uses t_point struct
// has cols colums for each row
// frees the matrix in case of malloc error
static t_point	**create_matrix(t_data *data)
{
	t_point	**matrix;
	int		i;

	matrix = (t_point **)malloc(sizeof(t_point *) * data->rows);
	if (!matrix)
		handle_error(MALLOC_ERROR, data);
	i = 0;
	while (i < data->rows)
	{
		matrix[i] = (t_point *)malloc(sizeof(t_point) * data->cols);
		if (!matrix[i])
		{
			free_matrix(matrix, --i);
			handle_error(MALLOC_ERROR, data);
		}
		initialize_row(&matrix, i, data->cols);
		i++;
	}
	return (matrix);
}

// gets the z value and the color for that specific element of the 2D matrix
static void	get_values(char *line, t_point ***mtx, int i)
{
	int		col_index;
	int		j;

	col_index = 0;
	j = 0;
	while (line[col_index] != '\n' && line[col_index] != '\0')
	{
		while (line[col_index] == ' ')
			col_index++;
		if (line[col_index] != '\n' && line[col_index] != '\0')
			(*mtx)[i][j].z = ft_atoi(&line[col_index]);
		if (line[col_index] != '\n' && line[col_index] != '\0')
			(*mtx)[i][j].proj_z = (*mtx)[i][j].z;
		while (ft_isdigit(line[col_index]) || line[col_index] == '-')
			col_index++;
		if (line[col_index] == ',')
		{
			col_index += 3;
			(*mtx)[i][j].color = ft_atoi_base(&line[col_index], BASE_16);
			(*mtx)[i][j].restore_color = (*mtx)[i][j].color;
			while (ft_strchr(BASE_HEXA, line[col_index]))
				col_index++;
		}
		j++;
	}
}

// populates the matrix one element at the time with get_values
static void	populate_matrix(t_point ***matrix, t_data *data, int fd)
{
	char	*current_line;
	int		i;

	i = 0;
	while (i < data->rows)
	{
		current_line = get_next_line(fd);
		get_values(current_line, matrix, i);
		free(current_line);
		i++;
	}
}

// needs data to have the number and cols previously known
// allocates memory for the matrix based on the number of rows and cols
// initializes it and populates it with the values read from the map file
// in case of malloc error frees and exits
t_point	**get_matrix(char *map_name, t_data *data)
{
	t_point	**matrix;
	int		fd;

	fd = open_file(map_name, data);
	matrix = create_matrix(data);
	populate_matrix(&matrix, data, fd);
	close(fd);
	return (matrix);
}
