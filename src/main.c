/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/03/26 21:03:52 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/27 23:19:40 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	fractol_init(&fractol);
	parse(&fractol, argc, argv);
	if (!fractol.mlx.ptr)
		graphics_init(&fractol);
	render(&fractol);
	show_controls();
	init_hooks(&fractol);
	mlx_loop(fractol.mlx.ptr);
}
