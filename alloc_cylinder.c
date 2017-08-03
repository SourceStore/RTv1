/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 13:51:11 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:44:49 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_cyl(char **str, t_scene **scene)
{
	t_cyl	*cyl;
	t_obj	*obj;

	if (len_matrix(str) != 11)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	cyl = (t_cyl *)malloc(sizeof(t_cyl));
	cyl->dot_0 = init_vec(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	cyl->nv = init_vec(ft_atoi(str[3]), ft_atoi(str[4]), ft_atoi(str[5]));
	cyl->uv = unit_vec(cyl->nv);
	cyl->col = init_col_al(ft_atoi(str[6]), ft_atoi(str[7]),
							ft_atoi(str[8]), ft_atoi(str[9]));
	cyl->r = ft_atoi(str[10]);
	if (cyl->r < 0)
		exit(write(1, "Invalid data\n", 14));
	obj = init_cylinder(cyl);
	if ((*scene)->head_o == NULL)
	{
		(*scene)->head_o = obj;
		(*scene)->last = obj;
	}
	else
		add_obj(scene, obj);
	(*scene)->count_obj++;
}

t_obj		*init_cylinder(t_cyl *cyl)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->data = cyl;
	obj->next = NULL;
	obj->get_color = get_color_cyl;
	obj->intersect = intersect_cyl;
	obj->get_hit_point = get_point_hit_cl;
	obj->get_norm_vec = get_norm_vector_cl;
	return (obj);
}

double		intersect_cyl(const void *data, t_ray *ray,
								double *t_0, double *t_1)
{
	t_cyl	cyl;
	double	a;
	double	b;
	double	c;
	double	s_qrt;

	cyl = (*(t_cyl*)data);
	a = dot_product(ray->dir, ray->dir) - SQR(dot_product(ray->dir, cyl.uv));
	b = 2.0 * (dot_product(ray->dir, margin_vectors(ray->pos, cyl.dot_0)) -
				(dot_product(ray->dir, cyl.uv) *
					dot_product(margin_vectors(ray->pos, cyl.dot_0), cyl.uv)));
	c = dot_product(margin_vectors(ray->pos, cyl.dot_0),
						margin_vectors(ray->pos, cyl.dot_0)) -
							SQR(dot_product(margin_vectors(ray->pos,
								cyl.dot_0), cyl.uv)) - SQR(cyl.r);
	s_qrt = SQR(b) - 4 * a * c;
	if (s_qrt < 0.0)
		return (-1);
	s_qrt = sqrt(s_qrt);
	*t_0 = (-b - s_qrt) / (2 * a);
	*t_1 = (-b + s_qrt) / (2 * a);
	return (return_value_cylinder(t_0, t_1, ray));
}

int			return_value_cylinder(double *t_0, double *t_1, t_ray *ray)
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

t_vec		get_norm_vector_cl(const void *data, t_ray *ray,
									t_vec p_hit, double min_dist)
{
	t_cyl	cyl;
	t_vec	norm;
	double	m;
	t_vec	center;

	cyl = (*(t_cyl*)data);
	center = margin_vectors(ray->pos, cyl.dot_0);
	m = dot_product(ray->dir, cyl.uv) * min_dist + dot_product(center, cyl.uv);
	norm = unit_vec(margin_vectors(margin_vectors(p_hit, cyl.dot_0),
										mult_coef(cyl.uv, m)));
	return (norm);
}
