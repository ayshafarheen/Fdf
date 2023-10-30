/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:15:15 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/07 14:33:09 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_bytes;
	int		endian;
	t_list	*data;
	int		count;
	int		width;
	int		startx;
	int		starty;
	void	**mlx_ptr;
	void	**win_ptr;
	int		height;
	double	a1;
	double	a2;
	double	a3;
	double	**rotation;
	int		line_count;
	int		scale;
	int		zval;
	double	**rot;
	double	**rot2;
	double	**prev_rot;
}	t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_line
{
	double	dx;
	double	dy;
	double	error;
	double	e2;
}	t_line;

void			print_matrix(double **arr, int row, int col);
void			ft_free(void **mat, int row);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			lst_print(t_list *nums, int count);
void			draw_row(t_data *img, t_list *cur, double *vals);
void			draw_img(t_data *img);
void			draw_line(int *vals, t_data *img, int color, int color2);
void			matmult(double **a, double *b, double ***loc);
double			**mat(double x, double y, double z);
unsigned int	convert_to_int(char *str);
void			gen_nums(char **lines, t_list *cur, int count);
void			parsing(int fd, t_data *img);
void			set_struct_vars(t_data **img);
void			inits(t_data **img, char *file, void **mlx_ptr, void **win_ptr);
int				key_hook(int keycode, t_data *vars);
void			rotation(t_data **img);
void			rotationx(t_data **img);
void			rotationy(t_data **img);
void			rotationz(t_data **img);
void			get_rgb(int color, t_color **color_rgb);
int				get_hex(int r, int g, int b);
int				*create_colors(t_color *color1, t_color *color2, int error);
void			draw_line(int *vals, t_data *img, int color, int color2);
int				terminate(t_data *img);
int				safely_terminate(t_data *img);
void			put_string(t_data **img);
void			error_handling(char *str, t_data *img);

#endif
