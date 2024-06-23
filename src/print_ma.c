#include "fdf.h"

void print_matrix(t_point **matrix, int rows, int cols)
{

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("x:%d, y:%d z:%d\npx:%d, py:%d pz:%d\n\n", matrix[i][j].x, matrix[i][j].proj_x, matrix[i][j].y, matrix[i][j].proj_z, matrix[i][j].z, matrix[i][j].proj_z);
        }
        printf("\n");
    }
}