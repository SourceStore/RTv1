# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/03 20:54:11 by rishchen          #+#    #+#              #
#    Updated: 2017/08/03 21:01:55 by rishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = alloc_camera.c alloc_cone.c alloc_cylinder.c alloc_light.c alloc_plane.c\
	alloc_scene.c alloc_sph.c auxiliary_functions.c auxiliary_functions_main.c\
	auxiliary_functions_parse.c ft_put_pixel.c get_color_from_objects.c\
	get_hit_points.c get_next_line.c init_auxiliary_vectors.c light_and_camera.c\
	main.c operations_vectors.c parse.c

INC = -I ft_fract.h -I mlx.h

OBJ = $(SRC:.c=.o)

LIBOBJ = make -C libft/

CFLAGS = -c -Wall -Werror -Wextra

MLXFLAGS = -framework OpenGL -framework AppKit

LIBINC = -L./libft -lft libmlx.a

all: $(NAME)

obj: $(OBJ)

$(NAME) : liball obj
	gcc $(OBJ) $(LIBINC) $(MLXFLAGS) -o $(NAME)

%.o: %.c 
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

liball:
	@make -C libft/ all

libclean:
	@make -C libft/ clean

libfclean:
	@make -C libft/ fclean

libre: libfclean liball
