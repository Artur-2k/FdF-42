# include "fdf.h"

void handle_error(int errnum)
{
    if (errnum == -1) // malloc error
        ft_putstr_fd("A malloc error occured\nTerminating!\n", 2);
    else if (errnum == -2) // read error
        ft_putstr_fd("A malloc error occured\nTerminating!\n", 2);
    else if (errnum == -3) // OPEN_ERROR	
        ft_putstr_fd("A malloc error occured\nTerminating!\n", 2);
    else if (errnum == -4) // CLOSE_ERROR
        ft_putstr_fd("A malloc error occured\nTerminating!\n", 2);

    //release_resources(); //TODO -----------------------------

    exit (1);
}