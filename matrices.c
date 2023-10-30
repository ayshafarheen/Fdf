/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:35:38 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/07 13:45:43 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matmult(double **a, double *b, double ***loc)
{
	loc[0][0][0] = a[0][0] * b[0] + a[0][1] * b[1] + a[0][2] * b[2];
	loc[0][1][0] = a[1][0] * b[0] + a[1][1] * b[1] + a[1][2] * b[2];
}

double	**mat(double x, double y, double z)
{
	double	**matrix;
	int		i;

	i = 0;
	matrix = malloc(3 * sizeof(double *));
	if (!matrix)
		return (0);
	while (i < 3)
	{
		matrix[i] = malloc(sizeof(double));
		if (!matrix[i++])
			return (0);
	}
	matrix[0][0] = x;
	matrix[1][0] = y;
	matrix[2][0] = z;
	return (matrix);
}
