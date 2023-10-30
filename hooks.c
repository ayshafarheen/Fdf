/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:08:25 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/07 14:35:22 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destroy_and_create(t_data **img)
{
	mlx_destroy_image(*((*img)->mlx_ptr), (*img)->img);
	(*img)->img = mlx_new_image((*img)->mlx_ptr, (*img)->width, (*img)->height);
	(*img)->addr = mlx_get_data_addr((*img)->img, &((*img)->bpp),
			&((*img)->line_bytes), &((*img)->endian));
	rotation(img);
	draw_img((*img));
	mlx_put_image_to_window(*((*img)->mlx_ptr), *((*img)->win_ptr),
		(*img)->img, 0, 0);
	put_string(img);
}

void	move(int keycode, t_data *img)
{
	if (keycode == 24)
		img->scale += 1;
	if (keycode == 27 && img->scale > 1)
		img->scale -= 1;
	if (keycode == 124)
		img->startx += 1;
	if (keycode == 123)
		img->startx -= 1;
	if (keycode == 126)
		img->starty -= 1;
	if (keycode == 125)
		img->starty += 1;
	destroy_and_create(&img);
}

void	rotation_movement(int keycode, t_data *img)
{
	if (keycode == 0)
		img->a1 -= 10 * M_PI / 180;
	if (keycode == 2)
		img->a1 += 10 * M_PI / 180;
	if (keycode == 1)
		img->a3 -= 10 * M_PI / 180;
	if (keycode == 13)
		img->a3 += 10 * M_PI / 180;
	if (keycode == 3)
		img->a2 -= 10 * M_PI / 180;
	if (keycode == 15)
		img->a2 += 10 * M_PI / 180;
	destroy_and_create(&img);
}

void	extras(int keycode, t_data *img)
{
	if (keycode == 6)
		img->zval++;
	if (keycode == 7)
		img->zval--;
	if (keycode == 34)
	{
		img->startx = 0;
		img->starty = 0;
		img->a1 = 45 * M_PI / 180;
		img->a2 = 0 * M_PI / 180;
		img->a3 = 35 * M_PI / 180;
		img->scale = img->width / img->count / 2;
	}
	if (keycode == 29)
	{
		img->a1 = 0;
		img->a2 = 0;
		img->a3 = 0;
	}
	destroy_and_create(&img);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 24 || keycode == 124 || keycode == 123
		|| keycode == 126 || keycode == 125 || keycode == 27)
		move(keycode, img);
	if (keycode == 0 || keycode == 1 || keycode == 13
		|| keycode == 2 || keycode == 15 || keycode == 3)
		rotation_movement(keycode, img);
	if (keycode == 6 || keycode == 7 || keycode == 34
		|| keycode == 29)
		extras(keycode, img);
	if (keycode == 53)
		safely_terminate(img);
	return (0);
}
