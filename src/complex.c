/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/17 18:28:45 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/21 00:50:25 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Adds two complex numbers
 * 
 * @param a Complex number
 * @param b Complex number
 * @return t_complex Sum result
******************************************************************************/
t_complex	add_complex(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

/******************************************************************************
 * @brief Gets the modulus of complex number
 * 
 * @param a Complex number
 * @return double Modulus
******************************************************************************/
double	mod_complex(t_complex a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

/******************************************************************************
 * @brief Gets the square of complex number
 * 
 * @param a Complex number
 * @return t_complex Square
******************************************************************************/
t_complex	square_complex(t_complex a)
{
	t_complex	c;

	c.x = a.x * a.x - a.y * a.y;
	c.y = 2 * a.x * a.y;
	return (c);
}

/******************************************************************************
 * @brief Gets absolute value of complex number
 * 
 * @param a Complex number
 * @return t_complex Absolute value
******************************************************************************/
t_complex	abs_complex(t_complex a)
{
	t_complex	c;

	c.x = fabs(a.x);
	c.y = fabs(a.y);
	return (c);
}
