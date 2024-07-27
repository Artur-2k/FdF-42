#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <X11/keysym.h>

# define BASE_16 "0123456789abcdef"
# define BASE_HEXA "0123456789abcdefABCDEF"

# define WIN_HEIGTH 800
# define WIN_LENGTH 1000  // Example values, adjust as needed

# ifndef M_PI  // If M_PI is not defined
#  define M_PI 3.14159  // Define a default value
# endif

# define SHIFT_VALUE 8
# define ANGLE_CHANGE 4

//struct for bresenham aka fak norminette
typedef struct s_bsnh
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
}	t_bsnh;

// STRUCT FOR EACH ELEMENT OF THE MAP
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		proj_x;
	int		proj_y;
	int		proj_z;
	int		color;
	int		restore_color;
}	t_point;

// projection boundaries
typedef struct s_boundaries
{
	int	maxx;
	int	maxy;
	int	maxz;
	int	minx;
	int	miny;
	int	minz;
}	t_boundaries;

typedef struct s_image
{
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_image;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	t_image			img;
	int				rows;
	int				cols;
	t_point			**matrix;
	t_boundaries	boundaries;
	double			scale;
	double			zscale;
	double			alpha;
	double			beta;
	double			gama;
	int				is_rotating;
	int				is_blinking;
	int				xoffset;
	int				yoffset;
	int				xtranslate;
	int				ytranslate;
}	t_data;

// ENUM FOR ALL THE ERRORS
typedef enum e_errors
{
	MALLOC_ERROR	= -1,
	READ_ERROR		= -2,
	OPEN_ERROR		= -3,
	MLX_ERROR		= -4,
	MAP_ERROR		= -5,
}	t_errors;

//*---------------------------------------------------------*//
//*							PROTOTYPES	                    *//
//*---------------------------------------------------------*//
//*															*//
//*------------------------free resources-------------------*//
void		free_matrix(t_point **matrix, int stopping_index);
int			exit_fdf(t_data *data);
void		handle_error(int errnum, t_data *data);

//*------------------------map reading----------------------*//
t_point		**get_matrix(char *map_name, t_data *data);
void		get_rows_and_cols(char *map_name, t_data *data);
void		get_bounderies(t_data *data);
int			get_offsets(t_data	*data);

//*------------------------matrix projections----------------*//
void		get_zoom(t_data *data);
void		reset_projections_set_zoom(t_data *data);
void		rotate_x(t_data *data, double alpha);
void		rotate_y(t_data *data, double beta);
void		rotate_z(t_data *data, double gama);
void		translate(t_data *data, int x_shift_value, int y_shift_value);

//*------------------------map drawing----------------------*//
void		put_pixel_to_img(t_image img, int x, int y, int color);
void		bresenham_part1(t_data *data, t_point A, t_point B);
void		draw_map(t_data *data);

//*------------------------image handeling------------------*//
void		new_image(t_data *data);
void		update_img(t_data *data);

//*------------------------utils----------------------------*//
int			get_min(int a, int b);
int			get_max(int a, int b);
void		rand_colors(t_data	*data);
int			open_file(char *map_name, t_data *data);
float		deg_to_rad(float deg);
float		normalize_angle(float angle);

//*------------------------controls-------------------------*//
int			read_keys(int key, t_data *data);
void		manual_translation(t_data *data, int key);
void		manual_rotate(t_data *data, int key);
void		manual_scale(t_data *data, int key);
void		manual_zscale(t_data *data, int key);
void		put_prespective(t_data *data, int key);
void		restart(t_data *data);

//*-----------------------animation------------------------*//
int			animation(t_data *data);
void		print_matrix(t_point **matrix, int rows, int cols);
#endif