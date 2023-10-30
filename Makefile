# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 09:59:04 by afarheen          #+#    #+#              #
#    Updated: 2023/05/08 08:30:35 by afarheen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

MY_SOURCES = main.c \
			utils.c \
			draw.c \
			matrices.c \
			struct_init.c \
			parsing.c \
			hooks.c \
			colors.c \
			bresenham.c

MY_OBJS = $(MY_SOURCES:.c=.o)

CFLAGS = -Imlx -Wall -Wextra -Werror -Ofast -march=native
MLXFLAGS = -L libft -l ft -Lminilibx -lmlx -framework OpenGL -framework AppKit

CC = gcc

all: $(NAME)

$(NAME): $(MY_OBJS)
	$(MAKE) -C libft
	$(MAKE) -C minilibx
	$(CC) $(CFLAGS) $(MY_SOURCES) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(MY_OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx clean
	rm -rf $(NAME) libft/libft.a
	rm -rf fdf.dSYM

re: fclean all