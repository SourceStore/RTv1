/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 20:43:45 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:44:18 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_conus(char **str, t_scene **scene)
{
	t_con	*con;
	t_obj	*obj;

	if (len_matrix(str) != 11)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	con = (t_con *)malloc(sizeof(t_con));
	con->dot_0 = init_vec(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	con->nv = init_vec(ft_atoi(str[3]), ft_atoi(str[4]), ft_atoi(str[5]));
	con->uv = unit_vec(con->nv);
	con->col = init_col_al(ft_atoi(str[6]), ft_atoi(str[7]),
			ft_atoi(str[8]), ft_atoi(str[9]));
	con->angle = ft_atoi(str[10]);
	obj = init_conus(con);
	if ((*scene)->head_o == NULL)
	{
		(*scene)->head_o = obj;
		(*scene)->last = obj;
	}
	else
		add_obj(scene, obj);
	(*scene)->count_obj++;
}

t_obj		*init_conus(t_con *con)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->data = con;
	obj->next = NULL;
	obj->get_color = get_color_conus;
	obj->intersect = intersect_conus;
	obj->get_hit_point = get_point_hit_cn;
	obj->get_norm_vec = get_norm_vector_cn;
	return (obj);
}

double		intersect_conus(const void *data, t_ray *ray,
								double *t_0, double *t_1)
{
	t_con	cone;
	double	a;
	double	b;
	double	c;
	double	s_qrt;

	cone = (*(t_con*)data);
	a = dot_product(ray->dir, ray->dir) -
		(1 + SQR(ANGLE(cone.angle))) * SQR(dot_product(ray->dir, cone.uv));
	b = 2.0 * (dot_product(ray->dir, margin_vectors(ray->pos, cone.dot_0)) -
			(1 + SQR(ANGLE(cone.angle))) * (dot_product(ray->dir, cone.uv) *
				dot_product(margin_vectors(ray->pos, cone.dot_0), cone.uv)));
	c = dot_product(margin_vectors(ray->pos, cone.dot_0),
						margin_vectors(ray->pos, cone.dot_0)) -
							(1 + SQR(ANGLE(cone.angle))) *
								SQR(dot_product(margin_vectors(ray->pos,
													cone.dot_0), cone.uv));
	s_qrt = SQR(b) - 4 * a * c;
	s_qrt = sqrt(s_qrt);
	*t_0 = (-b - s_qrt) / (2 * a);
	*t_1 = (-b + s_qrt) / (2 * a);
	return (return_value_cone(t_0, t_1, ray));
}

int			return_value_cone(double *t_0, double *t_1, t_ray *ray)
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

t_vec		get_norm_vector_cn(const void *data, t_ray *ray,
									t_vec p_hit, double min_dist)
{
	t_con	con;
	t_vec	norm;
	t_vec	center;
	double	m;

	con = (*(t_con*)data);
	center = margin_vectors(ray->pos, con.dot_0);
	m = dot_product(ray->dir, mult_coef(con.uv, min_dist)) +
		dot_product(center, con.uv);
	norm = unit_vec(margin_vectors(margin_vectors(p_hit, con.dot_0),
				mult_coef(con.uv, (1.0 + SQR(ANGLE(con.angle)) * m))));
	return (norm);
}
