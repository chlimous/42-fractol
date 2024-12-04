/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/07/06 21:20:31 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/07/06 21:28:19 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Maps x;y coordinates to a complex number on the plane
 * 
 * @param fractol Fractol pointer
 * @param x x coordinate
 * @param y y coordinate
 * @return t_complex Complex number
******************************************************************************/
t_complex	map_point(t_fractol *fractol, int x, int y)
{
	t_complex	c;
	double		length_x;
	double		length_y;

	length_x = fractol->view.max_x - fractol->view.min_x;
	length_y = fractol->view.max_y - fractol->view.min_y;
	c.x = fractol->view.min_x + (double)x / (WIDTH - 1) * length_x;
	if (fractol->set_handler == &burningship_set)
		c.y = -(fractol->view.max_y - (double)y / (HEIGHT - 1) * length_y);
	else
		c.y = fractol->view.max_y - (double)y / (HEIGHT - 1) * length_y;
	return (c);
}
