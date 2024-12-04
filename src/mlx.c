/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/17 18:23:07 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/27 23:36:37 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Initializes all graphic elements
 * 
 * @param fractol Fractol pointer
 * @return int Exit status
******************************************************************************/
int	graphics_init(t_fractol *fractol)
{
	fractol->mlx.ptr = mlx_init();
	if (!fractol->mlx.ptr)
		exit_fractol(EXIT_FAILURE, fractol);
	fractol->mlx.win = mlx_new_window(fractol->mlx.ptr, WIDTH, HEIGHT, \
			"fractol");
	if (!fractol->mlx.win)
		exit_fractol(EXIT_FAILURE, fractol);
	return (EXIT_SUCCESS);
}

/******************************************************************************
 * @brief Creates a new image and returns it
 * 
 * @param mlx_ptr mlx pointer
 * @return t_img New image, img.ptr sets to NULL in case of failure
******************************************************************************/
t_img	new_image(void *mlx_ptr)
{
	t_img	img;

	img.ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	if (img.ptr)
		img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, \
				&img.size_line, &img.endian);
	return (img);
}

/******************************************************************************
 * @brief Swaps color bytes order for big endian system
 * 
 * @param color Color ARGB code
 * @return int Exit status
******************************************************************************/
static int	swap_endian(int color)
{
	return (((color & 0xFF000000) >> 24) | \
		((color & 0x00FF0000) >> 8) | \
		((color & 0x0000FF00) << 8) | \
		((color & 0x000000FF) << 24));
}

/******************************************************************************
 * @brief Puts pixel on image
 * 
 * @param img Image pointer
 * @param x x coordinate
 * @param y y coordinate
 * @param color Color ARGB code
******************************************************************************/
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (img->endian == IS_BIG_ENDIAN)
		color = swap_endian(color);
	dst = img->addr + y * img->size_line + x * (img->bits_per_pixel / 8);
	*(int *)dst = color;
}
