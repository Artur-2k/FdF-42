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
	int		value;
	int		hexa;
}	t_point;

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
void		get_rows_and_cols(int fd, int *rows, int *cols);
void		free_matrix(t_point **matrix, int stopping_index);
t_point		**get_matrix(char *relative_path, int rows, int cols);

#endif