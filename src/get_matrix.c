/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:47 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 19:53:53 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	initialize_row(t_point ***matrix, int current_row, int cols)
{
	int j;

	j = 0;
	while (j < cols)
	{
		(*matrix)[current_row][j].x = j;
		(*matrix)[current_row][j].y = current_row;
		(*matrix)[current_row][j].z = 0; // Inicializa o valor com 0
		(*matrix)[current_row][j].proj_x = j;
		(*matrix)[current_row][j].proj_y = current_row;
		(*matrix)[current_row][j].proj_z = 0;
        (*matrix)[current_row][j].color = -1; // Inicializa o hexa com -1 (para quando não tem hexa)
        (*matrix)[current_row][j].restore_color = -1; // Inicializa o hexa com -1 (para quando não tem hexa)
		j++;
	}
}

// allocation of memory for the 2D matrix
// uses t_point for values and hexas
// has cols colums for each row
// frees the matrix in case of malloc error
static t_point	**create_matrix(t_data *data)
{
	t_point	**matrix;
	int i;

	matrix = (t_point **)malloc(sizeof(t_point *) * data->rows);
 	if (!matrix)
		handle_error(MALLOC_ERROR, data);
	i = 0;
	while (i < data->rows)
	{
		matrix[i] = (t_point *)malloc(sizeof(t_point) * data->cols);
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			handle_error(MALLOC_ERROR, data);
		}
		initialize_row(&matrix, i, data->cols);
		i++;
	}
	return (matrix);
}

// gets the value and the hexa for that specific element of the 2D matrix
static void	get_values(char *current_line, t_point ***matrix, int i)
{
	int		col_index;
	int		j;

	col_index = 0;
	j = 0;
	while (current_line[col_index] != '\n' && current_line[col_index] != '\0') //while not at the end of the row
	{
		while (current_line[col_index] == ' ') //skipar whitespaces
			col_index++;
		if (current_line[col_index] != '\n' && current_line[col_index] != '\0') // temos de ver se estou no fim antes de tentar escrever
			(*matrix)[i][j].proj_z = (*matrix)[i][j].z = ft_atoi(&current_line[col_index]); //ir buscar o valor | vai buscar até à , ou ao whitespace
		while (ft_isdigit(current_line[col_index]) || current_line[col_index] == '-') // vai skipar o valor
			col_index++;
		if (current_line[col_index] == ',') // se tiver , tem cor
		{
			col_index += 3; // skippar ,0x
			(*matrix)[i][j].color =ft_atoi_base(&current_line[col_index], BASE_16); //vai buscar a cor (retorna int)
			(*matrix)[i][j].restore_color = (*matrix)[i][j].color;
			while (ft_strchr(BASE_HEXA, current_line[col_index])) // vai skipar o hexa que pode ser maisculo ou minusculo
				col_index++;
		}
		j++;
	}
	free(current_line); // libertar o que se alocou
}
// populates the matrix one element at the time with get_values
static void	populate_matrix(t_point ***matrix, t_data *data, int fd)
{
	char *current_line;
	int i;

	i = 0;
	while (i < data->rows)
	{
		current_line = get_next_line(fd);
		if (!current_line)
			handle_error(READ_ERROR, data);
		get_values(current_line, matrix, i);
		i++;
	}
}

// opens up the file to get the number of rows and cols and then closes because of gnl
// allocates memory for the matrix
// opens and closes again the file to populate (needs to read the file to get the actual values and store it in the matrix)
t_point	**get_matrix(char *map_name, t_data *data)
{
	t_point	**matrix;
	int fd;

	fd = open_file(map_name, data);
	matrix = create_matrix(data);
	populate_matrix(&matrix, data, fd);
	close(fd);
	return (matrix);
}
