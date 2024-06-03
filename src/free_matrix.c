#include "../inc/fdf.h"

void	free_matrix(t_point **matrix, int stopping_index)
{
	int index;

	index = 0;
	while (index < stopping_index)
		free(matrix[index++]);
	free(matrix);
	return ;
}