/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/03/26 21:04:12 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/21 19:59:17 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <X11/keysym.h>

// mlx
# define IS_LITTLE_ENDIAN 0
# define IS_BIG_ENDIAN 1

// X11
# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define DESTROY 17
# define LEFT_MOUSE_BTN 1
# define RIGHT_MOUSE_BTN 3

# define WIDTH 1000
# define HEIGHT 500

# define MIN_ITER 1
# define MAX_ITER 1000

# define BOUND 2

# define SET_0 "julia"
# define SET_1 "mandelbrot"
# define SET_2 "burningship"

# define COLORS_QTY 4

typedef struct s_fractol	t_fractol;

typedef void				(*t_set_handler)(t_fractol *, int, int);

typedef struct s_view
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
}	t_view;

typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
}	t_mlx;

struct s_fractol
{
	t_mlx			mlx;
	t_set_handler	set_handler;
	t_complex		c;
	unsigned int	max_iter;
	t_view			view;
	int				color;
};

/* mlx */
int			graphics_init(t_fractol *fractol);
t_img		new_image(void *mlx_ptr);
void		put_pixel(t_img *img, int x, int y, int color);

/* Colors */
void		put_pixel_convergence(t_fractol *fractol, \
				t_coordinates coordinates);
void		put_pixel_divergence(t_fractol *fractol, \
				t_coordinates coordinates, int iter, t_complex z);

/* Hooks */
void		init_hooks(t_fractol *fractol);

/* Complex numbers */
t_complex	add_complex(t_complex a, t_complex b);
double		mod_complex(t_complex a);
t_complex	square_complex(t_complex a);
t_complex	abs_complex(t_complex a);

/* Animations */
void		animation_init(t_fractol *fractol);
int			animate(t_fractol *fractol);

/* Sets */
void		burningship_set(t_fractol *fractol, int x, int y);
void		julia_set(t_fractol *fractol, int x, int y);
void		mandelbrot_set(t_fractol *fractol, int x, int y);

/* Fractals */
void		fractol_init(t_fractol *fractol);
int			render(t_fractol *fractol);

/* Mapping */
t_complex	map_point(t_fractol *fractol, int x, int y);

/* Parser */
int			parse(t_fractol *fractol, int argc, char **argv);
void		show_help(void);
int			is_a_number(char *str);

/* Utils */
void		exit_fractol(int exit_status, t_fractol *fractol);
int			exit_destroy(t_fractol *fractol);
void		exit_help(int exit_status, t_fractol *fractol);
void		show_controls(void);

#endif
