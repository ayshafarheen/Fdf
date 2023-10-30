/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:53:20 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/07 14:00:46 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	step(int *p2, int *p1, double *error, double dp)
{
	*error = *error + dp;
	if (*p1 < *p2)
		*p1 = *p1 + 1;
	else
		*p1 = *p1 - 1;
}

/*
vals - x0 y0 x1 y1
E2 is kind of a decision parameter which decies whether we will be stepping
x or y. The step value is determined in the step function whihc goes forward
or backward depending on the value. The values or continuously stepped until
they become equal to the final values.
*/
void	draw_pixels(int *vals, t_data *img, int *color_list, t_line line)
{
	int	i;

	i = 0;
	while (1)
	{
		my_mlx_pixel_put(img, vals[0], vals[1], color_list[i]);
		if (vals[1] == vals[3] && vals[2] == vals[0])
			break ;
		line.e2 = 2 * line.error;
		if (line.e2 <= line.dx)
		{
			if (vals[3] == vals[1])
				break ;
			step(&vals[3], &vals[1], &(line.error), line.dx);
		}
		if (line.e2 >= line.dy)
		{
			if (vals[0] == vals[2])
				break ;
			step(&vals[2], &vals[0], &(line.error), line.dy);
		}
		i++;
	}
}

/*
get the rgb of the start color and end color and make a color list
for each pixel.
it calculates an understanding of the difference between the beginning x's
and beginning y's and then draws the pixels between these values.
*/
void	draw_line(int *vals, t_data *img, int color, int color2)
{
	t_color	*color1_rgb;
	t_color	*color2_rgb;
	int		*color_list;
	t_line	line;

	get_rgb(color, &color1_rgb);
	get_rgb(color2, &color2_rgb);
	color_list = create_colors(color1_rgb, color2_rgb, abs(vals[2]
				- vals[0]) + abs(vals[3] - vals[1]));
	free(color1_rgb);
	free(color2_rgb);
	line.dx = abs(vals[2] - vals[0]);
	line.dy = -abs(vals[3] - vals[1]);
	line.error = line.dx + line.dy;
	draw_pixels(vals, img, color_list, line);
	free(color_list);
}
