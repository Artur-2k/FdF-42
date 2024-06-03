#include "../inc/fdf.h"

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
void	get_rows_and_cols(int fd, int *rows, int *cols)
{
	char *current_line;

	*rows = 0;
	*cols = 0;

	current_line = get_next_line(fd);
	//todo gnl Error managment
	/* if (!current_line)
	{
	}*/
	*cols = count_elements(current_line);
	while (current_line)
	{
		free(current_line);
		(*rows)++;
		current_line = get_next_line(fd);
		//todo gnl Error managment
		/* if (!current_line)
		{
		} */
	}
	free(current_line);
	return ;
}
