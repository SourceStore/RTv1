/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:37:13 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/02 18:44:46 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_put_pixel(t_scene *scene, double x, double y, t_col color)
{
	if (x >= 0 && y >= 0 && x < W && y < H)
	{
		scene->addr[(int)x * 4 +
				(int)y * scene->sl] = (unsigned char)color.r;
		scene->addr[(int)x * 4 + 1 +
					(int)y * scene->sl] = (unsigned char)color.g;
		scene->addr[(int)x * 4 + 2 +
					(int)y * scene->sl] = (unsigned char)color.b;
		scene->addr[(int)x * 4 + 3 +
					(int)y * scene->sl] = (unsigned char)color.o;
	}
}

int			set_functions(int keykode, t_scene **scene)
{
	if (keykode == 53 || keykode == 65307)
		close_win(keykode);
	if (keykode == 125 || keykode == 126 || keykode == 123 || keykode == 124)
		move_camera(keykode, *scene);
	else if (keykode == 41 || keykode == 42 || keykode == 39 || keykode == 33)
		change_dir_light(keykode, *scene);
	else if (keykode == 69 || keykode == 78)
		change_focal_camera(keykode, *scene);
	mlx_destroy_image((*scene)->mlx, (*scene)->img);
	mlx_clear_window((*scene)->mlx, (*scene)->win);
	(*scene)->img = mlx_new_image((*scene)->img, W, H);
	(*scene)->addr = mlx_get_data_addr((*scene)->img, &(*scene)->bpp,
										&(*scene)->sl, &(*scene)->endian);
	start_point(*scene);
	mlx_put_image_to_window((*scene)->mlx, (*scene)->win, (*scene)->img, 0, 0);
	return (0);
}

t_col		mult_col(t_col col, double k)
{
	t_col		col_a;

	col_a.r = col.r * k;
	col_a.g = col.g * k;
	col_a.b = col.b * k;
	col_a.o = col.o * k;
	return (col_a);
}

void		clamp(t_col *color)
{
	color->r = color->r < 0.0 ? 0.0 : color->r;
	color->g = color->g < 0.0 ? 0.0 : color->g;
	color->b = color->b < 0.0 ? 0.0 : color->b;
	color->r = color->r > 255.0 ? 255.0 : color->r;
	color->g = color->g > 255.0 ? 255.0 : color->g;
	color->b = color->b > 255.0 ? 255.0 : color->b;
}
