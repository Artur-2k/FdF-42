#include "fdf.h"

void	initialization(char *map_name, t_map *map)
{

	map->map_name = ft_strdup(map_name);
	get_rows_and_cols(map_name, map);
	map->matrix = get_matrix(map->map_name, map->rows, map->cols);
}


int main(int ac, char **av)
{
	t_map	map;

	initialization(av[1], &map);
	//TESTE A MATRIZ
	print_matrix(map.matrix, map.rows, map.cols);

	free_matrix(map.matrix, map.rows);

	return (0);
}