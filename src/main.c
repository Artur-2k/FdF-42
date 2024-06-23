/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:34:55 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 22:50:30 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_check(int ac, char **av);
void	initialization(char *map_name, t_data *data);
void	start_map(t_data *data);
void	print_instructions(void);

int	main(int ac, char **av)
{
	t_data	data;

	error_check(ac, av);
	// inits mlx_ptr, win, img,matrix from map values,bools and data stuff
	initialization(av[1], &data);
	// gets scale, rotates for isometric,	centers the map and prints it
	start_map(&data);
	print_instructions();
	//	key presses -> read_keys with param data + key pressed
	mlx_key_hook(data.mlx_win, read_keys, &data);
	// on the event mask keypress on the destroynotify -> exit_fdf
	mlx_hook(data.mlx_win, DestroyNotify, 1L << 0, exit_fdf, &data);
	// keeps a while true loop on the backcground for this
	// animation function basically
	mlx_loop_hook(data.mlx_ptr, animation, &data);
	// keeps the connenction running on the background basically
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	error_check(int ac, char **av)
{
	int	str_len;
	int	fd;

	if (ac != 2 || !av[1])
	{
		ft_putstr_fd("Wrong inputs! Use: ./fdf map_path\n", 2);
		exit(1);
	}
	str_len = ft_strlen(av[1]);
	if (str_len <= 4 || ft_strncmp(&av[1][str_len - 4], ".fdf", 3))
	{
		ft_putstr_fd("Invalid map format!\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening the file\nTerminating!\n", 2);
		exit(1);
	}
	close(fd);
	return ;
}

void	start_map(t_data *data)
{
	get_zoom(data);
	rotate_x(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->alpha)));
	rotate_z(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->gama)));
	rotate_y(data, DEG_TO_RAD(NORMALIZE_ANGLE(data->beta)));
	get_bounderies(data);
	get_offsets(data);
	translate(data, data->xoffset, data->yoffset);
	draw_map(data);
}

void	initialization(char *map_name, t_data *data)
{
	// MLX init
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		handle_error(MLX_ERROR, data);
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIN_LENGTH, WIN_HEIGTH,
			"FdF do Arturzao");
	if (!data->mlx_win)
		handle_error(MLX_ERROR, data);
	new_image(data);
	if (!data->img.img_ptr)
		handle_error(MLX_ERROR, data);
	// Animation off
	data->is_rotating = 0;
	data->is_blinking = 0;
	// Scale
	data->scale = 0;
	data->zscale = 1;
	// Rotation angles
	data->alpha = 45;
	data->beta = -35;
	data->gama = 30;
	// Offset
	data->xoffset = 0;
	data->yoffset = 0;
	// Translation added
	data->xtranslate = 0;
	data->ytranslate = 0;
	// get map dimensions and map itself (calls handle_error inside)
	get_rows_and_cols(map_name, data);
	data->matrix = get_matrix(map_name, data);
}

void	print_instructions(void)
{
	ft_printf("           Instructions\n");
	ft_printf("------------Translation----------\n");
	ft_printf("|    		X axis: h/l  	|\n");
	ft_printf("|    		Y axis: j/k    	|\n");
	ft_printf("|------------Rotation-----------|\n");
	ft_printf("|    		X axis: w/s    	|\n");
	ft_printf("|    		Y axis: a/d    	|\n");
	ft_printf("|    		Z axis: q/e    	|\n");
	ft_printf("|-------------Scale-------------|\n");
	ft_printf("|    		More zoom: t       |\n");
	ft_printf("|    		Less zoom: y       |\n");
	ft_printf("|-------------Z Scale-----------|\n");
	ft_printf("|    		More height: z     |\n");
	ft_printf("|    		Less height: x     |\n");
	ft_printf("|-----------Projections---------|\n");
	ft_printf("|           Top view: 1         |\n");
	ft_printf("|    		Paralel view: 2 	|\n");
	ft_printf("|------------Animations---------|\n");
	ft_printf("|    		Rotating: r    	|\n");
	ft_printf("|    		Blinking: b    	|\n");
	ft_printf("|--------------Other------------|\n");
	ft_printf("|	Press enter to reset    |\n");
	ft_printf("|     Press c to change color   |\n");
	ft_printf("---------------------------------\n\t\t\tartur-2k\n");
	ft_printf("Exit by pressing ESC\n");
}
