/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/23 02:53:37 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/23 02:55:56 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Initializes fractol parameters for animation
 * 
 * @param fractol Fractol pointer
******************************************************************************/
void	animation_init(t_fractol *fractol)
{
	fractol->set_handler = &julia_set;
	fractol->c.x = 0.5;
	fractol->c.y = 1;
}

/******************************************************************************
 * @brief Animates Julia fractal by shifting the constant on each frame
 * 
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
int	animate(t_fractol *fractol)
{
	static int			sign_x = 1;
	static int			sign_y = 1;
	static uintmax_t	count_x;
	static uintmax_t	count_y;

	if (fractol->c.x > 0.5)
	{
		sign_x = -1;
		++count_x;
	}
	else if (fractol->c.x < -1)
		sign_x = 1;
	if (fractol->c.y > 0.75)
	{
		sign_y = -1;
		++count_y;
	}
	else if (fractol->c.y < -1)
		sign_y = 1;
	fractol->c.x += (0.02 + count_x % 3 * 0.01) * sign_x;
	fractol->c.y += (0.03 + count_y % 3 * 0.01) * sign_y;
	return (render(fractol), EXIT_SUCCESS);
}
