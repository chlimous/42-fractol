/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlimous <chlimous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:37:51 by chlimous          #+#    #+#             */
/*   Updated: 2024/11/21 20:00:08 by chlimous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/******************************************************************************
 * @brief Shows input help
 * 
******************************************************************************/
void	show_help(void)
{
	ft_dprintf(2, "./fractol julia (r [-1000.0, 1000.0] i [-1000.0, 1000.0] "\
			"(iterations [1, 1000]))\n");
	ft_dprintf(2, "./fractol mandelbrot (iterations [1, 1000])\n");
	ft_dprintf(2, "./fractol burningship (iterations [1, 1000])\n");
	ft_dprintf(2, "./fractol animation\n");
}

/******************************************************************************
 * @brief Check if the string is a number
 *
 * @param str String
 * @return int Returns 1 if it is a number, else 0
******************************************************************************/
int	is_a_number(char *str)
{
	int	point;
	int	i;

	i = 0;
	if (str[i] == '-')
		++i;
	if (str[i] == '.')
		return (0);
	point = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (point == 1)
				return (0);
			else
				point = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
