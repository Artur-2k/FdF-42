#include "fdf.h"

void print_matrix(t_point **matrix, int rows, int cols)
{

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("(%d, %d) ", matrix[i][j].value, matrix[i][j].hexa);
        }
        printf("\n");
    }
}