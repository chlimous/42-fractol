/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/19 00:30:43 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/23 04:34:05 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Calculates Burning Ship fractal state for x;y coordinates.
	zn+1 = (|zn|)^2 + c, z0 = 0, c being the current point in the complex plane
 * 
 * @param fractol Fractol pointer
 * @param x x coordinate
 * @param y y coordinate
******************************************************************************/
void	burningship_set(t_fractol *fractol, int x, int y)
{
	t_coordinates	coordinates;
	t_complex		z;
	unsigned int	i;

	coordinates.x = x;
	coordinates.y = y;
	z.x = 0;
	z.y = 0;
	fractol->c = map_point(fractol, x, y);
	i = 0;
	while (i < fractol->max_iter)
	{
		z = add_complex(square_complex(abs_complex(z)), fractol->c);
		if (mod_complex(z) > BOUND)
		{
			put_pixel_divergence(fractol, coordinates, i, z);
			break ;
		}
		++i;
	}
	if (i == fractol->max_iter)
		put_pixel_convergence(fractol, coordinates);
}

/******************************************************************************
 * @brief Calculates Mandelbrot fractal state for x;y coordinates.
	zn+1 = zn^2 + c, z0 = 0, c being the current point in the complex plane
 * 
 * @param fractol Fractol pointer
 * @param x x coordinate
 * @param y y coordinate
******************************************************************************/
void	mandelbrot_set(t_fractol *fractol, int x, int y)
{
	t_coordinates	coordinates;
	t_complex		z;
	unsigned int	i;

	coordinates.x = x;
	coordinates.y = y;
	z.x = 0;
	z.y = 0;
	fractol->c = map_point(fractol, x, y);
	i = 0;
	while (i < fractol->max_iter)
	{
		z = add_complex(square_complex(z), fractol->c);
		if (mod_complex(z) > BOUND)
		{
			put_pixel_divergence(fractol, coordinates, i, z);
			break ;
		}
		++i;
	}
	if (i == fractol->max_iter)
		put_pixel_convergence(fractol, coordinates);
}

/******************************************************************************
 * @brief Calculates Julia fractal state for x;y coordinates.
 	zn+1 = zn^2 + c, z0 being the current point in the complex plane
	and c being a constant
 * 
 * @param fractol Fractol pointer
 * @param x x coordinate
 * @param y y coordinate
******************************************************************************/
void	julia_set(t_fractol *fractol, int x, int y)
{
	t_coordinates	coordinates;
	t_complex		z;
	unsigned int	i;

	coordinates.x = x;
	coordinates.y = y;
	z = map_point(fractol, x, y);
	i = 0;
	while (i < fractol->max_iter)
	{
		z = add_complex(square_complex(z), fractol->c);
		if (mod_complex(z) > BOUND)
		{
			put_pixel_divergence(fractol, coordinates, i, z);
			break ;
		}
		++i;
	}
	if (i == fractol->max_iter)
		put_pixel_convergence(fractol, coordinates);
}
