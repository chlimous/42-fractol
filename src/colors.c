/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/19 00:23:36 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/23 17:37:21 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Puts colored pixel on image for converging sequence
 * 
 * @param fractol Fractol pointer
 * @param coordinates Pixel coordinate
******************************************************************************/
void	put_pixel_convergence(t_fractol *fractol, t_coordinates coordinates)
{
	const int	colors[COLORS_QTY] = {0, 1, 10, 316};

	put_pixel(&fractol->mlx.img, coordinates.x, coordinates.y, 0xFF000000 \
		+ colors[fractol->color] \
		* (int)fabs((double)(coordinates.x + coordinates.y)));
}

/******************************************************************************
 * @brief Puts colored pixel on image for diverging sequence
 * 
******************************************************************************/
void	put_pixel_divergence(t_fractol *fractol, t_coordinates coordinates, \
		int iter, t_complex z)
{
	double	smooth;
	int		color;

	smooth = iter + 1 - (log((log(mod_complex(z)))) / log(2));
	color = 13283165 * smooth / fractol->max_iter;
	put_pixel(&fractol->mlx.img, coordinates.x, coordinates.y, color);
}
