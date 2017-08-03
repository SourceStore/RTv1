/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_sph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:17:33 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:45:53 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_sphere(char **str, t_scene **scene)
{
	t_sph	*sph;
	t_obj	*obj;

	if (len_matrix(str) != 8)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	sph = (t_sph *)malloc(sizeof(t_sph));
	sph->pos = init_vec(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	sph->col = init_col_al(ft_atoi(str[3]), ft_atoi(str[4]),
							ft_atoi(str[5]), ft_atoi(str[6]));
	sph->r = ft_atoi(str[7]);
	if (sph->r < 0)
		exit(write(1, "Invalid data\n", 14));
	obj = init_sphere(sph);
	if (((*scene)->head_o) == NULL)
	{
		(*scene)->head_o = obj;
		(*scene)->last = obj;
	}
	else
		add_obj(scene, obj);
	(*scene)->count_obj++;
}

t_obj		*init_sphere(t_sph *sph)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->data = sph;
	obj->next = NULL;
	obj->intersect = intersect_sphere;
	obj->get_color = get_color_sphere;
	obj->get_center = get_center_sph;
	obj->get_hit_point = get_point_hit_s;
	obj->get_norm_vec = get_norm_vector_s;
	return (obj);
}

t_vec		get_norm_vector_s(const void *data, t_ray *ray,
								t_vec p_hit, double min_dist)
{
	t_sph	sph;
	t_vec	norm;

	mult_coef(ray->pos, 1);
	min_dist *= 1;
	sph = (*(t_sph*)data);
	norm = unit_vec(margin_vectors(p_hit, sph.pos));
	return (norm);
}

double		intersect_sphere(const void *data, t_ray *ray,
								double *t_0, double *t_1)
{
	t_sph	sph;
	double	b;
	double	c;
	t_vec	dist;
	double	discr;

	sph = (*(t_sph *)data);
	dist = margin_vectors(ray->pos, sph.pos);
	b = 2 * dot_product(ray->dir, dist);
	c = dot_product(dist, dist) - SQR(sph.r);
	discr = SQR(b) - 4 * c;
	if (discr < 0)
		return (-1);
	discr = sqrt(discr);
	*t_0 = (-b - discr) / (2);
	*t_1 = (-b + discr) / (2);
	return (return_value_sphere(t_0, t_1, ray));
}

int			return_value_sphere(double *t_0, double *t_1, t_ray *ray)
{
	if (*t_0 > *t_1)
		ft_swap(t_0, t_1);
	if (*t_0 < 0)
	{
		*t_0 = *t_1;
		if (*t_0 < 0.00001f)
			return (-1);
	}
	if (fabs(*t_0) < ray->t)
		return (1);
	return (-1);
}
