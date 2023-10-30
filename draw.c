/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:36:29 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/08 08:28:29 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

/*
creates a vector from given points.
multiplies vector with rotation matrix to obtain rotated version of that point.
draw a line form prev point to current point.
*/
double	**horizontal(int *vals, t_data *img, t_list *cur, double **prev_rot)
{
	double	rot[3];
	int		x;
	int		y;
	int		i;
	int		z;

	x = vals[0];
	y = vals[1];
	i = vals[2];
	if (cur->nums[i] >= 1)
		z = cur->nums[i] + img->zval;
	else
		z = cur->nums[i];
	rot[0] = x * img->scale;
	rot[1] = y * img->scale;
	rot[2] = z * img->scale;
	matmult(img->rotation, rot, &(img->rot));
	if (i > 0)
	{
		draw_line((int []){prev_rot[0][0] + img->width / 2, prev_rot[1][0]
			+ img->height / 2, img->rot[0][0] + img->width / 2, img->rot[1][0]
			+ img->height / 2}, img, cur->colors[i - 1], cur->colors[i]);
	}
	return (img->rot);
}

/*
check whether or not any elevation needs to be done and then draw a
line from prev point to current point similar to done in horizontal.
*/
void	vertical(int *vals, t_data *img, t_list *cur, double **prev_rot)
{
	double	rot[3];
	int		x1;
	int		y1;
	int		z;
	int		i;

	x1 = vals[0];
	y1 = vals[1];
	i = vals[2];
	if (cur->next)
	{
		if (cur->next->nums[i] >= 1)
			z = cur->next->nums[i] + img->zval;
		else
			z = cur->next->nums[i];
		rot[0] = x1 * img->scale;
		rot[1] = (y1 + 1) * img->scale;
		rot[2] = z * img->scale;
		matmult(img->rotation, rot, &(img->rot2));
		draw_line((int []){prev_rot[0][0] + img->width / 2, prev_rot[1][0]
			+ img->height / 2, img->rot2[0][0] + img->width / 2, img->rot2[1][0]
			+ img->height / 2}, img, cur->colors[i], cur->next->colors[i]);
	}
}

/*
call drawins to the right of a given point and bottom of a given oint.
*/
void	draw_row(t_data *img, t_list *cur, double *vals)
{
	int		i;
	double	**prev_rot;
	int		x1;
	int		y1;

	x1 = vals[0];
	y1 = vals[1];
	i = 0;
	while (i < img->count)
	{
		prev_rot = horizontal((int []){x1, y1, i}, img, cur, img->prev_rot);
		img->prev_rot[0][0] = prev_rot[0][0];
		img->prev_rot[1][0] = prev_rot[1][0];
		vertical((int []){x1, y1, i}, img, cur, img->prev_rot);
		i++;
		x1 += 1;
	}
}

/*
draws all the rows one by one
*/
void	draw_img(t_data *img)
{
	t_list	*cur;
	double	y1;
	int		center;

	img->rot = mat(0, 0, 0);
	img->rot2 = mat(0, 0, 0);
	img->prev_rot = mat(0, 0, 0);
	center = img->count / 2;
	y1 = img->starty - img->line_count / 2;
	cur = img->data;
	while (cur)
	{
		draw_row(img, cur, (double []){img->startx - center, y1});
		y1 += 1;
		cur = cur -> next;
	}
	ft_free((void **)img->rot, 3);
	ft_free((void **)img->rot2, 3);
	ft_free((void **)img->prev_rot, 3);
}
