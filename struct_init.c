/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:37:16 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/17 11:01:17 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Set rotation matrix.
*/
void	rotation(t_data **img)
{
	double	a3;
	double	a2;
	double	a1;

	a1 = (*img)->a1;
	a2 = (*img)->a2;
	a3 = (*img)->a3;
	(*img)->rotation[0][0] = cos(a1) * cos(a2);
	(*img)->rotation[0][1] = -sin(a1);
	(*img)->rotation[0][2] = cos(a1) * sin(a2);
	(*img)->rotation[1][0] = cos(a2) * sin(a1) * cos(a3) + sin(a3) * sin(a2);
	(*img)->rotation[1][1] = cos(a3) * cos(a1);
	(*img)->rotation[1][2] = cos(a3) * sin(a1) * sin(a2) - sin(a3) * cos(a2);
}

/*
Set the required variables to isometric orientation.
*/
void	set_struct_vars(t_data **img)
{
	double	gamma;
	double	beta;
	double	alpha;
	int		i;

	i = 0;
	alpha = 45 * M_PI / 180;
	beta = 0 * M_PI / 180;
	gamma = 35 * M_PI / 180;
	(*img)->startx = 0;
	(*img)->line_count = 0;
	(*img)->starty = 0;
	(*img)->width = 1500;
	(*img)->height = 1500;
	(*img)->scale = 2;
	(*img)->a1 = alpha;
	(*img)->a2 = beta;
	(*img)->a3 = gamma;
	while (i < 3)
	{
		(*img)->rotation[i] = malloc(3 * sizeof(double));
		if (!(*img)->rotation[i++])
			return ;
	}
	rotation(img);
}

/*
Allocate required memr for all variables. Check for right file format and
accessibillity. initialize window and required window vars.
*/
void	inits(t_data **img, char *file, void **mlx_ptr, void **win_ptr)
{
	int	fd;

	(*img) = ft_calloc(1, sizeof(t_data));
	if (!(*img))
		return ;
	(*img)->mlx_ptr = mlx_ptr;
	(*img)->win_ptr = win_ptr;
	(*img)->rotation = malloc(3 * sizeof(double *));
	if (!(*img)->rotation)
		return ;
	set_struct_vars(img);
	fd = open(file, O_RDWR);
	if (fd < 0 || ft_strcmp(ft_strstr(file, "."), ".fdf") != 0)
		error_handling("Error: invalid file\n", *img);
	parsing(fd, *img);
	*mlx_ptr = mlx_init();
	*win_ptr = mlx_new_window(*mlx_ptr, (*img)->width, (*img)->height, "mlx");
	(*img)->img = mlx_new_image(*mlx_ptr, (*img)->width, (*img)->height);
	(*img)->addr = mlx_get_data_addr((*img)->img, &((*img)->bpp),
			&((*img)->line_bytes), &((*img)->endian));
}
