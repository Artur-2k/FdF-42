#include "../inc/fdf.h"

int main(void)
{
	//TODO Verificar a terminação do mapa e se só tem um mapa
	char *relative_path = "test_maps/mars.fdf";
	// test_maps/basictest.fdf sem erro
	// test_maps/mars.fdf sem erro
	// test_maps/leak.fdf	  sem erros?!??!?!?!
	// test_maps/10-2.fdf    sem erro
	int		fd;
	int		rows;
	int		cols;

	fd = open(relative_path, O_RDONLY);
 	if (fd == -1)
	{
		perror("Could not open file");
		close(fd);
		exit(OPEN_ERROR);
	}
	get_rows_and_cols(fd, &rows, &cols);
	close(fd);

	printf("%d %d\n", rows, cols);

	//TODO GET THE MATRIX
	t_point	**matrix = get_matrix(relative_path, rows, cols);

	//TESTE A MATRIZ
	print_matrix(matrix, rows, cols);

	free_matrix(matrix, rows);

	return (0);
}