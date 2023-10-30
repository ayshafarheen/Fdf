/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:08:42 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/07 14:31:22 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img;

	if (argc == 2)
	{
		inits(&img, argv[1], &mlx_ptr, &win_ptr);
		img->scale = img->width / img->count / 2;
		img->zval = 0;
		draw_img(img);
		mlx_put_image_to_window(mlx_ptr, win_ptr, img->img, 0, 0);
		mlx_hook(win_ptr, 2, 1L << 1, key_hook, img);
		mlx_hook(win_ptr, 17, 0, safely_terminate, img);
		put_string(&img);
		mlx_loop(mlx_ptr);
	}
	else
		write(2, "Error Invalid number of arguments!\n", 35);
	return (0);
}
