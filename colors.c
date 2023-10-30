/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:49:52 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/03 11:12:25 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Convert int to rgb
R epresents the first part of the number, G the second and B the last
*/
void	get_rgb(int color, t_color **color_rgb)
{
	*color_rgb = malloc(sizeof(t_color));
	if (!(*color_rgb))
		return ;
	(*color_rgb)->b = color % 256;
	(*color_rgb)->g = ((color - (*color_rgb)->b) / 256) % 256;
	(*color_rgb)->r = ((color - (*color_rgb)->b) / pow(256, 2))
		- (*color_rgb)->g / 256;
}

int	get_hex(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

/*
using the number of pixels that would be required to go from the first
point to the second, we calculate different colors for each pixel by
increasing the rgb vlaues by a certain percentage at each step till
it becomes 100% -> final color.
*/
int	*create_colors(t_color *color1, t_color *color2, int error)
{
	int		*color_list;
	int		i;
	double	part;
	double	percent;
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (0);
	i = 0;
	color_list = malloc((error + 1) * sizeof(int));
	if (!color_list)
		return (0);
	part = (double)100 / error;
	while (i <= error)
	{
		percent = ((part) * i) / 100;
		color->r = color1->r + percent * (color2->r - color1->r);
		color->g = color1->g + percent * (color2->g - color1->g);
		color->b = color1->b + percent * (color2->b - color1->b);
		color_list[i] = get_hex(color->r, color->g, color->b);
		i++;
	}
	free(color);
	return (color_list);
}
