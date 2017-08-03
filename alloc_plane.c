/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:17:22 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:44:53 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_plane(char **str, t_scene **scene)
{
	t_pl	*pl;
	t_obj	*obj;

	if (len_matrix(str) != 10)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	pl = (t_pl *)malloc(sizeof(t_pl));
	pl->dot_0 = init_vec(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	pl->nv = init_vec(ft_atoi(str[3]), ft_atoi(str[4]), ft_atoi(str[5]));
	pl->uv = unit_vec(pl->nv);
	pl->col = init_col_al(ft_atoi(str[6]), ft_atoi(str[7]),
							ft_atoi(str[8]), ft_atoi(str[9]));
	obj = init_plane(pl);
	if ((*scene)->head_o == NULL)
	{
		(*scene)->head_o = obj;
		(*scene)->last = obj;
	}
	else
		add_obj(scene, obj);
	(*scene)->count_obj++;
}

t_obj		*init_plane(t_pl *pl)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->data = pl;
	obj->next = NULL;
	obj->get_color = get_color_plane;
	obj->intersect = intersect_plane;
	obj->get_hit_point = get_point_hit_p;
	obj->get_norm_vec = get_norm_vector_p;
	return (obj);
}

t_vec		get_norm_vector_p(const void *data, t_ray *ray,
									t_vec p_hit, double min_dist)
{
	t_pl	pl;
	t_vec	norm;

	mult_coef(ray->pos, 1);
	min_dist *= 1;
	mult_coef(p_hit, 1);
	pl = (*(t_pl*)data);
	norm = mult_coef(pl.nv, -1);
	return (norm);
}

double		intersect_plane(const void *data, t_ray *ray,
									double *t_0, double *t_1)
{
	t_pl	pl;
	t_vec	vec;
	double	dot_norms;

	pl = (*(t_pl *)data);
	dot_norms = dot_product(ray->dir, pl.uv);
	if (dot_norms == 0)
		return (-1);
	vec = margin_vectors(ray->pos, pl.dot_0);
	*t_0 = dot_product(mult_coef(vec, -1), pl.uv) / dot_norms;
	if (*t_0 < 0.001f)
		return (-1);
	if (*t_0 > 0 && len_vect(ray->vec) < ray->t)
	{
		*t_1 = *t_0;
		return (1);
	}
	return (-1);
}
