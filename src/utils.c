/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/17 18:55:22 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/21 19:32:25 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Frees all heap memory and exit program
 * 
 * @param exit_status Exit status
 * @param fractol Fractol pointer
******************************************************************************/
void	exit_fractol(int exit_status, t_fractol *fractol)
{
	if (fractol->mlx.img.ptr)
		mlx_destroy_image(fractol->mlx.ptr, fractol->mlx.img.ptr);
	if (fractol->mlx.win)
		mlx_destroy_window(fractol->mlx.ptr, fractol->mlx.win);
	if (fractol->mlx.ptr)
	{
		mlx_destroy_display(fractol->mlx.ptr);
		free(fractol->mlx.ptr);
	}
	exit(exit_status);
}

/******************************************************************************
 * @brief Exit function used by DESTROY hook
 * 
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
int	exit_destroy(t_fractol *fractol)
{
	exit_fractol(EXIT_SUCCESS, fractol);
	return (EXIT_SUCCESS);
}

/******************************************************************************
 * @brief Shows help and frees all heap memory and exit program
 *
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
void	exit_help(int exit_status, t_fractol *fractol)
{
	show_help();
	exit_fractol(exit_status, fractol);
}

/******************************************************************************
 * @brief Shows keyboard and mouse controls
 * 
******************************************************************************/
void	show_controls(void)
{
	ft_printf("Zoom: Mouse Wheel or + -\n");
	ft_printf("Move: WASD or Arrows\n");
	ft_printf("Shift Colors: Space\n");
	ft_printf("Shift Iterations: [ ]\n");
	ft_printf("Exit: Escape\n");
}
