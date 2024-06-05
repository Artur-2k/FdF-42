# include "fdf.h"

int	open_file(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
        handle_error(OPEN_ERROR);
	return (fd);
}