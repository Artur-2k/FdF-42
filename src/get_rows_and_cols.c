#include "fdf.h"

// counts the number of elements of a line that ends in a \0 or a \n and is separated by spaces
int		count_elements(char *current_line)
{
    int index = 0;
    int elements = 0;
    int flag = 0;

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
// cols uses count_elements and i just need to count the first time cuz every row has the same ammount of cols
void	get_rows_and_cols(char *map_name, t_map *map)
{
	char *current_line;
	int	fd;

	map->cols = 0;
	map->rows = 0;
	fd = open_file(map_name);
	current_line = get_next_line(fd);
	if (!current_line)
		handle_error(READ_ERROR);
	map->cols = count_elements(current_line);
	while (current_line)
	{
		free(current_line);
		(map->rows)++;
		current_line = get_next_line(fd);
	}
	free(current_line);
	close(fd);
	if (map->rows != map->cols)
		handle_error(READ_ERROR);
	return ;
}
