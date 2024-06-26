/*
				TODO
prettify the roadmap of this project understanding and add some more study material
*/

read the map and store it into a 2d matrix that stores points coordinates and color
	mallocs for 2d arrays
	get_next_line
		open
		read
		close
	retriving the specific data for each data of the point

inicialize the mlx stuff
	mlx_init
	mlx_new_window
	mlx_new_image
	mlx_loop

start the map
	get the appropriete scale
	rotate the pixel coordinates on x,y,z
		matrix rotations
	find map bounderies and set the map to the middle of the window
	draw the map connecting every vertex to the right and down (execept last ones)
		pixel to image (find memory offset for coloring pixels)
		bresenhams line algorithm
		mlx_put_image_to_window

read inpus
	key_hooks
		define keybindings
		for rotation
			+/- angle for key press
			matrix_rotations
			euler (gimbal lock) for rotation axis parenting (x->z->y)
			map_update
				destroy image and create a new one (could also bzero everything probably more efficient);
		for translation
			+/- shift on x/y for key press
			map_update
	mouse_hooks





https://www.youtube.com/watch?v=zc8b2Jo7mno

Euler (gimball lock)

