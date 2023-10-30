/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:37:52 by afarheen          #+#    #+#             */
/*   Updated: 2023/05/05 14:59:55 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Function to convert string to num.
*/
unsigned int	convert_to_int(char *str)
{
	int	num;
	int	len;
	int	i;

	str = str + 2;
	len = ft_strlen(str) - 1;
	i = 0;
	num = 0;
	while (i <= len)
	{
		if (str[i] >= '0' && str[i] <= '9' )
			num += (str[i] - '0') * pow(16, len - i);
		else if (str[i] >= 'a' && str[i] <= 'z')
			num += (str[i] - 'a' + 10) * pow(16, len - i);
		else if (str[i] >= 'A' && str[i] <= 'Z')
			num += (str[i] - 'A' + 10) * pow(16, len - i);
		i++;
	}
	return (num);
}

/*
For all the lines we store a linked list which contains information of which
contaims the colors and requied z values. The colors are converted to the int
value and if no color is given, white is stored.
*/
void	gen_nums(char **lines, t_list *cur, int count)
{
	int		i;
	char	*color;

	i = 0;
	cur->nums = malloc(count * sizeof(int));
	if (!cur->nums)
		return ;
	cur->colors = malloc(count * sizeof(unsigned int));
	if (!cur->colors)
		return ;
	while (lines[i])
	{
		color = ft_strchr(lines[i], ',');
		if (color)
			cur->colors[i] = convert_to_int(color + 1);
		else
			cur->colors[i] = 0xffffff;
		cur->nums[i] = ft_atoi(lines[i]);
		i++;
	}
	ft_free((void **)lines, count);
}

/*
read all the lines and store the required information
*/
void	parsing(int fd, t_data *img)
{
	char	*line;
	char	**numbers;
	char	*nl_pos;
	t_list	*cur;

	line = get_next_line(fd);
	img->count = 0;
	if (!line)
		error_handling("Error: map is empty\n", img);
	while (line)
	{
		nl_pos = ft_strchr(line, '\n');
		if (nl_pos)
			nl_pos[0] = 0;
		numbers = ft_split(line, ' ');
		cur = ft_lstnew(line);
		ft_lstadd_back(&img->data, cur);
		if (img->count == 0)
			while (numbers[img->count])
				img->count++;
		gen_nums(numbers, cur, img->count);
		img->line_count++;
		free(line);
		line = get_next_line(fd);
	}
}
