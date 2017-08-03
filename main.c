/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 16:01:02 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 19:09:21 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** gcc *.c -framework OpenGl -framework AppKit libft/libft.a libmlx.a -o RTV1
*/

t_col		traced_color(t_scene *scene, t_light *light)
{
	scene->obj = scene->head_o;
	scene->col_buff = (*scene).o_inter->get_color((*scene).o_inter->data);
	init_ray_to_light(scene, light);
	if (len_vect(scene->raytl.vec) <= scene->head_l->t)
	{
		while (scene->obj)
		{
			if (scene->obj->intersect(scene->obj->data, &scene->raytl,
											&scene->t_0, &scene->t_1) != -1)
			{
				scene->col_buff = init_col(0, 0, 0, 0);
				break ;
			}
			scene->obj = scene->obj->next;
		}
		if (scene->obj == NULL)
		{
			algorithm_blinn_lambert(scene);
			color_mixing(scene);
		}
	}
	else
		scene->col_buff = init_col(0, 0, 0, 0);
	return (scene->col_buff);
}

t_col		trace(t_scene *scene)
{
	t_light	*light;
	t_col	traced_col;
	t_col	final;

	light = scene->head_l;
	final = init_col(0, 0, 0, 0);
	while (light != NULL)
	{
		traced_col = traced_color(scene, light);
		final.r += traced_col.r;
		final.g += traced_col.g;
		final.b += traced_col.b;
		clamp(&final);
		light = light->next;
	}
	final.o = 30;
	return (final);
}

void		intersect_cam_ray_with_objects(t_scene *scene, int x, int y)
{
	t_obj	*obj;

	scene->o_inter = NULL;
	obj = scene->head_o;
	while (obj)
	{
		if (obj->intersect(obj->data, scene->ray,
								&(scene->t_0), &(scene->t_1)) != -1)
		{
			if (scene->t_0 < scene->min_dist)
			{
				scene->min_dist = scene->t_0;
				(*scene).o_inter = obj;
			}
		}
		obj = obj->next;
	}
	if (scene->o_inter != NULL)
	{
		scene->final_color = trace(scene);
		ft_put_pixel(scene, x, y, scene->final_color);
	}
}

void		start_point(t_scene *scene)
{
	double	x;
	double	y;
	double	i;
	double	j;

	scene->image_asp_ratio = (double)W / (double)H;
	scene->scale = tan(ANGLE(scene->cam->focus / 2));
	y = -1;
	while (++y < H)
	{
		x = -1;
		j = 1.0 - 2.0 * ((y + 0.5) / H) * scene->scale;
		while (++x < W)
		{
			i = (2.0 * ((x + 0.5)) / W - 1.0) *
							scene->scale * scene->image_asp_ratio;
			scene->min_dist = INFINITY;
			init_ray(scene, i, j);
			intersect_cam_ray_with_objects(scene, x, y);
		}
	}
}

int			main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2 || ft_strcmp("data.obj", av[1]))
	{
		perror("Error");
		exit(0);
	}
	scene = init_scene();
	core_point_check(ac, av, scene);
	if (scene->cam == NULL || scene->head_l == NULL)
		exit(write(1, "Sorry, no data for light or camera!\n", 36));
	start_point(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img, 0, 0);
	loop_point(scene);
	return (0);
}
