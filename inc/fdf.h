#ifndef FDF_H
# define FDF_H

#include "get_next_line.h"
#include "libft.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>

#define BASE_16 "0123456789abcdef"
#define BASE_xX "0123456789abcdefABCDEF"

// STRUCT FOR EACH ELEMENT OF THE MAP
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		hexa;
}	t_point;

typedef struct s_map
{
	char *map_name;
	int rows;
	int cols;
	t_point **matrix;
}	t_map;

// ENUM FOR ALL THE ERRORS
typedef enum e_errors
{
	MALLOC_ERROR 	= -1,
	READ_ERROR		= -2,
	OPEN_ERROR		= -3,
	CLOSE_ERROR		= -4,
}	t_errors;

//*				PROTOTYPES				*//

void 		print_matrix(t_point **matrix, int rows, int cols);
void	get_rows_and_cols(char *map_name, t_map *map);
void		free_matrix(t_point **matrix, int stopping_index);
t_point		**get_matrix(char *map_name, int rows, int cols);
int	open_file(char *map_name);
void handle_error(int errnum);

#endif