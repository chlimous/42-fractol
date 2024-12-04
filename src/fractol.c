/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/17 18:51:22 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/09/09 01:13:31 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Initialize fractol structure
 * 
 * @param fractol Fractol pointer
******************************************************************************/
void	fractol_init(t_fractol *fractol)
{
	int	lowest;

	ft_bzero(fractol, sizeof(t_fractol));
	fractol->max_iter = 20;
	fractol->c.x = -1;
	fractol->c.y = 0;
	if (WIDTH >= HEIGHT)
		lowest = HEIGHT;
	else
		lowest = WIDTH;
	fractol->view.max_x = 2 * WIDTH / lowest;
	fractol->view.min_x = -2 * WIDTH / lowest;
	fractol->view.max_y = 2 * HEIGHT / lowest;
	fractol->view.min_y = -2 * HEIGHT / lowest;
}

/******************************************************************************
 * @brief Puts iterations and view informations on screen
 * 
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
static void	put_str_screen(t_fractol *fractol)
{
	char	*str;

	if (ft_asprintf(&str, "Iterations: %u", fractol->max_iter) == -1)
		exit_fractol(EXIT_FAILURE, fractol);
	mlx_string_put(fractol->mlx.ptr, fractol->mlx.win, 10, 20, \
			0xFFFFFFFF, str);
	free(str);
	if (ft_asprintf(&str, "X: %e | %e", fractol->view.min_x, \
				fractol->view.max_x) == -1)
		exit_fractol(EXIT_FAILURE, fractol);
	mlx_string_put(fractol->mlx.ptr, fractol->mlx.win, 10, 40, \
			0xFFFFFFFF, str);
	free(str);
	if (ft_asprintf(&str, "Y: %e | %e", fractol->view.min_y, \
				fractol->view.max_y) == -1)
		exit_fractol(EXIT_FAILURE, fractol);
	mlx_string_put(fractol->mlx.ptr, fractol->mlx.win, 10, 60, \
			0xFFFFFFFF, str);
	free(str);
}

/******************************************************************************
 * @brief Calculates fractal state for each pixel of the image
 * 
 * @param fractol Fractol pointer
******************************************************************************/
static void	fractal(t_fractol *fractol)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			fractol->set_handler(fractol, x, y);
			++y;
		}
		++x;
	}
}

/******************************************************************************
 * @brief Renders new frame and puts it on screen
 * 
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
int	render(t_fractol *fractol)
{
	void	*img_old_ptr;
	t_img	img_new;

	img_old_ptr = fractol->mlx.img.ptr;
	img_new = new_image(fractol->mlx.ptr);
	if (!img_new.ptr)
		exit_fractol(EXIT_FAILURE, fractol);
	fractol->mlx.img = img_new;
	fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.ptr, fractol->mlx.win, \
			fractol->mlx.img.ptr, 0, 0);
	put_str_screen(fractol);
	if (img_old_ptr)
		mlx_destroy_image(fractol->mlx.ptr, img_old_ptr);
	return (EXIT_SUCCESS);
}
