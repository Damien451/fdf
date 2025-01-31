/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:38:14 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/07 15:45:14 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define MAX_PROJ 2
# define MAX_DRAW 2
# define FOV 110.0 * M_PI / 180.0
# define FAR 10.0
# define NEAR 0.1
# define C_GROUND 0x6B4C2F
# define C_DEEP 0x4C99
# define C_SUMMIT 0xFF8000
# define C_10 0x247524
# define C_20 0x2A892A
# define C_35 0x309C30
# define C_50 0x37B337
# define C_200 0x4FC94F
# define C_300 0x666666
# define C_450 0xD9D9D9
# define C_650 0xffffff

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef enum		e_error
{
	ok,
	falloc,
	usage,
	filepath,
	badline
}					t_error;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				stride;
	int				endian;
}					t_img;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_line
{
	char			*line;
	int				nbx;
	struct s_line	*next;
}					t_line;

typedef struct		s_matrix
{
	double			m[4][4];
}					t_matrix;

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector3;

typedef struct		s_cam
{
	t_vector3		pos;
	t_matrix		projection[2];
	t_matrix		rotation;
	t_vector3		rot_angles;
	t_vector3		pre_rot_angles;
}					t_cam;

typedef struct		s_parser
{
	char			*fname;
	int				fd;
	t_line			*lines;
	t_line			*last_line;
	int				maxz;
	int				minz;
}					t_parser;

typedef struct		s_canvas
{
	void			*mlx_ptr;
	void			*window;
	t_img			img;
	double			w_height;
	double			w_width;
}					t_canvas;

typedef struct		s_crea
{
	t_bool			mode;
	t_point			current;
}					t_crea;

typedef struct		s_func
{
	void			(*f)();
}					t_func;

typedef	struct		s_xiao
{
	int				color;
	int				steep;
	int				xpx11;
	int				xpx12;
	int				x;
	double			dx;
	double			dy;
	double			gradient;
	double			inter;
	double			rel;
	double			pos;
}					t_xiao;

typedef struct		s_fdf
{
	t_parser		parser;
	t_canvas		canvas;
	t_cam			cam;
	t_vector3		*map;
	t_vector2		*project;
	int				height;
	int				width;
	t_matrix		unit;
	t_matrix		rot_x;
	t_matrix		rot_y;
	t_matrix		rot_z;
	int				proj;
	double			speed;
	double			relief;
	t_func			f[2];
	int				drawer;
	t_crea			crea;
	t_bool			hud;
}					t_fdf;

/*
** Open the file
*/
t_error				ft_open_file(int ac, char **av, t_fdf *fdf);

/*
** Initialize fdf struct
*/
void				ft_init_fdf(t_fdf *fdf);

/*
** Parse the file
*/
t_error				ft_parse_file(t_fdf *fdf);

/*
** Get the file's data to create the map into fdf struct
*/
t_error				ft_create_map(t_fdf *fdf);

/*
** Leave the file according to the situation
*/
int					ft_leave(t_error ret, t_fdf *fdf);

/*
** Free the map's lines
*/
void				free_lines(t_fdf *fdf);

/*
** Initialize three different matrixes
*/
void				init_matrixes(t_fdf *fdf);

/*
** Manage keys input
*/
int					key_hook(int key, t_fdf *fdf);

/*
** Display the map on the mlx screen
*/
int					draw_map(t_fdf *fdf);

/*
** Multiply matrixes
*/
t_matrix			mat_4_mul(int nb, ...);

/*
** Put pixels between two points
*/
void				bresenham(t_fdf *fdf, t_point o, t_point t, t_point color);

/*
** Put lines on screen
*/
void				put_line(t_fdf *fdf, int ox, int oy);

/*
** Multiply a matrix with a vector
*/
t_vector3			mat_4_mul_v(t_matrix m, t_vector3 v);

/*
** Get pixel color
*/
int					get_color(int from, int to, double a);

/*
** Add two vectors
*/
t_vector3			vec_3_add(t_vector3 a, t_vector3 b);

/*
** Sub two vectors
*/
t_vector3			vec_3_sub(t_vector3 a, t_vector3 b);

/*
** Manage the rotation matrixes
*/
void				rotator(t_fdf *fdf, t_vector3 a);

/*
** Call ft_leave if a leave call is send
*/
int					hook_leave(t_fdf *fdf);

/*
** Return a color gradient
*/
double				get_gradient(double val, double first, double second);

/*
**	Manage antialiasing
*/
void				xiaolin(t_fdf *fdf, t_point o, t_point t, t_point color);

/*
** Put a pixel on the window
*/
void				put_pixel(t_fdf *fdf, int x, int y, int color);

/*
** Select a color for a point, depending on its altitude
*/
void				select_color(t_fdf *fdf, int i);

/*
** Reset the cam position
*/
void				reset_cam(t_fdf *fdf);

/*
**	Calls line drawers
*/
int					put_pixels(t_fdf *fdf);

/*
** Put a circle around a point in creative mode
*/
void				put_circle(t_fdf *fdf);

/*
**	Project a 3D point in 2D
*/
t_vector2			project_point(t_fdf *fdf, int x, int y);

/*
**	Swap two integer pointers
*/
void				swap(int *a, int *b);

#endif
