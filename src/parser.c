/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/18 20:05:38 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/21 20:00:48 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Parses maximum iterations option
 * 
 * @param fractol Fractol pointer
 * @param iter Maximum iterations
******************************************************************************/
static void	parse_iter(t_fractol *fractol, char *iter)
{
	int	res;

	res = 0;
	if (*iter == '+')
		++iter;
	while (ft_isdigit(*iter))
	{
		res = res * 10 + ft_ascii_to_nb(*iter);
		if (res > MAX_ITER)
		{
			show_help();
			exit_fractol(EXIT_FAILURE, fractol);
		}
		++iter;
	}
	if (res < MIN_ITER)
	{
		show_help();
		exit_fractol(EXIT_FAILURE, fractol);
	}
	fractol->max_iter = res;
}

/******************************************************************************
 * @brief Parses set
 * 
 * @param fractol Fractol pointer
 * @param set Set name
******************************************************************************/
static void	parse_set(t_fractol *fractol, char *set)
{
	const char			*sets[] = {SET_0, SET_1, SET_2, 0};
	const t_set_handler	set_handler[] = \
		{julia_set, mandelbrot_set, burningship_set, 0};
	unsigned int		i;

	i = 0;
	while (sets[i])
	{
		if (!ft_strcmp(set, sets[i]))
			fractol->set_handler = set_handler[i];
		++i;
	}
	if (fractol->set_handler == NULL)
		exit_help(EXIT_FAILURE, fractol);
}

/******************************************************************************
 * @brief Parses all options
 * 
 * @param fractol Fractol pointer
 * @param argc Amount of arguments
 * @param argv Arguments
******************************************************************************/
static void	parse_options(t_fractol *fractol, int argc, char **argv)
{
	if (fractol->set_handler == &julia_set)
	{
		if (argc == 4 || argc == 5)
		{
			fractol->c.x = ft_atof(argv[2]);
			fractol->c.y = ft_atof(argv[3]);
			if (fractol->c.x < -1000.0 || fractol->c.x > 1000.0 \
			|| fractol->c.y < -1000.0 || fractol->c.y > 1000.0)
				exit_help(EXIT_FAILURE, fractol);
		}
		else if (argc == 3)
			exit_help(EXIT_FAILURE, fractol);
		if (argc == 5)
			parse_iter(fractol, argv[4]);
	}
	else
	{
		if (argc == 3)
			parse_iter(fractol, argv[2]);
		else if (argc > 3)
			exit_help(EXIT_FAILURE, fractol);
	}
}

/******************************************************************************
 * @brief Parses command
 * 
 * @param fractol Fractol pointer
 * @param argc Amount of arguments
 * @param argv Arguments
 * @return int Exit status
******************************************************************************/
int	parse(t_fractol *fractol, int argc, char **argv)
{
	if (argc < 2 || argc > 5 || (argc >= 3 && !is_a_number(argv[2])) \
	|| (argc >= 4 && !is_a_number(argv[3])) || \
	(argc == 5 && !is_a_number(argv[4])))
		exit_help(EXIT_FAILURE, fractol);
	if (!ft_strcmp(argv[1], "animation") && argc == 2)
	{
		graphics_init(fractol);
		animation_init(fractol);
		mlx_loop_hook(fractol->mlx.ptr, &animate, fractol);
		return (EXIT_SUCCESS);
	}
	parse_set(fractol, argv[1]);
	parse_options(fractol, argc, argv);
	return (EXIT_SUCCESS);
}
