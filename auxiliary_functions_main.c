/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions_main.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 18:27:13 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:21:56 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene		*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->head_o = NULL;
	scene->head_l = NULL;
	scene->o_inter = NULL;
	scene->cam = NULL;
	scene->f_alloc = (t_checker *)malloc(sizeof(t_checker));
	scene->ray = (t_ray *)malloc(sizeof(t_ray));
	scene->f_alloc->f_cam = 0;
	scene->f_alloc->f_sph = 0;
	scene->f_alloc->f_pl = 0;
	scene->f_alloc->f_con = 0;
	scene->f_alloc->f_cyl = 0;
	scene->f_alloc->f_l_s = 0;
	scene->count_obj = 0;
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, W, H, "RTv1");
	scene->img = mlx_new_image(scene->mlx, W, H);
	scene->addr = mlx_get_data_addr(scene->img, &scene->bpp,
										&scene->sl, &scene->endian);
	return (scene);
}

void		loop_point(t_scene *scene)
{
	mlx_hook(scene->win, 17, 0, &exit_win, scene);
	mlx_hook(scene->win, 2, 1 << 7, set_functions, &scene);
	mlx_loop(scene->mlx);
}

void		init_ray_to_light(t_scene *scene, t_light *light)
{
	(*scene).o_inter->get_hit_point(scene->ray,
										scene->min_dist, &(scene->p_hit));
	scene->n_hit = (*scene).o_inter->get_norm_vec((*scene).o_inter->data,
									scene->ray, scene->p_hit, scene->min_dist);
	scene->raytl.vec = margin_vectors(light->loc_w, scene->p_hit);
	scene->raytl.pos = scene->p_hit;
	scene->raytl.dir = unit_vec(scene->raytl.vec);
	scene->raytl.t = len_vect(scene->raytl.vec);
}

void		algorithm_blinn_lambert(t_scene *scene)
{
	scene->lambert = fmax(dot_product(scene->n_hit, scene->raytl.dir), 0.0);
	scene->rayty.vec = margin_vectors(scene->cam->pos, scene->p_hit);
	scene->rayty.dir = unit_vec(scene->rayty.vec);
	scene->h = add_vector(scene->raytl.dir, scene->rayty.dir);
	scene->h.x /= len_vect(add_vector(scene->raytl.dir, scene->rayty.dir));
	scene->h.y /= len_vect(add_vector(scene->raytl.dir, scene->rayty.dir));
	scene->h.z /= len_vect(add_vector(scene->raytl.dir, scene->rayty.dir));
	scene->h = unit_vec(scene->h);
	scene->spec = mult_col(init_col_al(180, 180, 180, 255),
					pow(fmax(dot_product(scene->n_hit, scene->h), 0.0), 70));
}

void		color_mixing(t_scene *scene)
{
	scene->col_buff.r = (int)((((scene->lambert * scene->col_buff.r
						+ scene->spec.r)) * 255 > 255) ? 255 : (scene->lambert *
								scene->col_buff.r + scene->spec.r) * 255);
	scene->col_buff.g = (int)((((scene->lambert * scene->col_buff.g +
						scene->spec.g)) * 255 > 255) ? 255 : (scene->lambert *
									scene->col_buff.g + scene->spec.g) * 255);
	scene->col_buff.b = (int)((((scene->lambert * scene->col_buff.b +
						scene->spec.b)) * 255 > 255) ? 255 : (scene->lambert *
									scene->col_buff.b + scene->spec.b) * 255);
}
