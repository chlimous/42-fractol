/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/18 00:25:29 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/09/19 21:25:44 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Handles zoom and shifts view
 * 
 * @param button Key
 * @param x Zoom x coordinate
 * @param y Zoom y coordinate
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
static int	handle_zoom(int button, int x, int y, t_fractol *fractol)
{
	int		sign;
	double	zoom_x;
	double	zoom_y;

	sign = 0;
	if (button == MOUSE_DOWN || button == XK_equal)
		sign = 1;
	else if (button == MOUSE_UP || button == XK_minus)
		sign = -1;
	zoom_x = (fractol->view.max_x - fractol->view.min_x) * 0.1;
	zoom_y = (fractol->view.max_y - fractol->view.min_y) * 0.1;
	if (((zoom_x < 0.000000000000001 || zoom_y < 0.000000000000001) \
	&& sign == 1) || ((zoom_x > 2e80 || zoom_y > 2e80) && sign == -1))
		return (EXIT_FAILURE);
	fractol->view.max_x = fractol->view.max_x \
		- (zoom_x * ((double)1 - (double)x / (WIDTH - 1))) * sign;
	fractol->view.min_x = fractol->view.min_x \
		+ (zoom_x * (((double)x / (WIDTH - 1)))) * sign;
	fractol->view.max_y = fractol->view.max_y \
		- (zoom_y * ((double)y / (HEIGHT - 1))) * sign;
	fractol->view.min_y = fractol->view.min_y \
		+ (zoom_y * ((double)1 - (double)y / (HEIGHT - 1))) * sign;
	return (EXIT_SUCCESS);
}

/******************************************************************************
 * @brief Handles mouse keys
 * 
 * @param button Key
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
static int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	t_complex	c;

	if (button == LEFT_MOUSE_BTN && fractol->set_handler == &julia_set)
	{
		c = map_point(fractol, x, y);
		if (c.x < -1000.0 || c.x > 1000.0 || c.y < -1000.0 \
				|| c.y > 1000.0)
			ft_printf("Error. Constant interval: [-1000.0, 1000.0]\n");
		else
		{
			fractol->c = c;
			ft_printf("Constant set: %f%+fi\n", \
					fractol->c.x, fractol->c.y);
		}
		render(fractol);
	}
	else if (button == MOUSE_DOWN || button == MOUSE_UP || button == XK_equal \
			|| button == XK_minus)
	{
		if (handle_zoom(button, x, y, fractol) == EXIT_SUCCESS)
			render(fractol);
	}
	return (EXIT_SUCCESS);
}

/******************************************************************************
 * @brief Handles view shift
 * 
 * @param keycode Key
 * @param fractol Fractol pointer
******************************************************************************/
static void	handle_key_move(int keycode, t_fractol *fractol)
{
	double	length_x;
	double	length_y;

	length_x = fractol->view.max_x - fractol->view.min_x;
	length_y = fractol->view.max_y - fractol->view.min_y;
	if (keycode == XK_Up || keycode == XK_w)
	{
		fractol->view.max_y = fractol->view.max_y + 0.1 * length_y;
		fractol->view.min_y = fractol->view.min_y + 0.1 * length_y;
	}
	else if (keycode == XK_Down || keycode == XK_s)
	{
		fractol->view.max_y = fractol->view.max_y - 0.1 * length_y;
		fractol->view.min_y = fractol->view.min_y - 0.1 * length_y;
	}
	else if (keycode == XK_Left || keycode == XK_a)
	{
		fractol->view.max_x = fractol->view.max_x - 0.1 * length_x;
		fractol->view.min_x = fractol->view.min_x - 0.1 * length_x;
	}
	else if (keycode == XK_Right || keycode == XK_d)
	{
		fractol->view.max_x = fractol->view.max_x + 0.1 * length_x;
		fractol->view.min_x = fractol->view.min_x + 0.1 * length_x;
	}
}

/******************************************************************************
 * @brief Handles keyboard strokes
 * 
 * @param keycode Key
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
static int	handle_key(int keycode, t_fractol *fractol)
{
	if (keycode == XK_Escape)
		exit_fractol(EXIT_SUCCESS, fractol);
	else if (keycode == XK_space)
	{
		if (fractol->color == COLORS_QTY - 1)
			fractol->color = 0;
		else
			++fractol->color;
	}
	else if (keycode == XK_equal || keycode == XK_minus)
		handle_zoom(keycode, WIDTH / 2, HEIGHT / 2, fractol);
	else if (keycode == XK_bracketleft && fractol->max_iter > MIN_ITER)
		--fractol->max_iter;
	else if (keycode == XK_bracketright && fractol->max_iter < MAX_ITER)
		++fractol->max_iter;
	else if (keycode == XK_Up || keycode == XK_w || keycode == XK_Down || \
			keycode == XK_s || keycode == XK_Left || keycode == \
			XK_a || keycode == XK_Right || keycode == XK_d)
		handle_key_move(keycode, fractol);
	render(fractol);
	return (EXIT_SUCCESS);
}

/******************************************************************************
 * @brief Initializes keys and mouse hooks
 * 
 * @param fractol Fractol pointer
******************************************************************************/
void	init_hooks(t_fractol *fractol)
{
	mlx_key_hook(fractol->mlx.win, &handle_key, fractol);
	mlx_mouse_hook(fractol->mlx.win, &handle_mouse, fractol);
	mlx_hook(fractol->mlx.win, DESTROY, 0, &exit_destroy, fractol);
}
