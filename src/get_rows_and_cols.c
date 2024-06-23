/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rows_and_cols.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:52 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:10:03 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// counts the number of elements of a line that ends in a
//\0 or a \n and is separated by spaces
int	count_elements(char *current_line)
{
	int	index;
	int	elements;
	int	flag;

	index = 0;
	elements = 0;
	flag = 0;
	while (current_line[index] != '\0' && current_line[index] != '\n')
	{
		if (current_line[index] != ' ')
		{
			if (flag == 0)
			{
				flag = 1;
				elements++;
			}
		}
		else
			flag = 0;
		index++;
	}
	return (elements);
}

// changes the number of rows and cols
// each call of get next line means one line and that means plus one row
// cols uses count_elements and i just need to count the first
// time cuz every row has the same ammount of cols
void	get_rows_and_cols(char *map_name, t_data *data)
{
	char	*current_line;
	int		fd;

	data->cols = 0;
	data->rows = 0;
	fd = open_file(map_name, data);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		exit(1);
	data->cols = count_elements(current_line);
	while (current_line)
	{
		free(current_line);
		(data->rows)++;
		current_line = get_next_line(fd);
	}
	if (current_line)
		free(current_line);
	close(fd);
	return ;
}
