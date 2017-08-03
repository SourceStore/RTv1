/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 18:06:50 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 18:17:50 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_point_hit_p(t_ray *ray, double min_dist, t_vec *p_hit)
{
	*p_hit = add_vector(ray->pos, mult_coef(ray->dir, min_dist));
}

void		get_point_hit_s(t_ray *ray, double min_dist, t_vec *p_hit)
{
	*p_hit = add_vector(ray->pos, mult_coef(ray->dir, min_dist));
}

void		get_point_hit_cn(t_ray *ray, double min_dist, t_vec *p_hit)
{
	*p_hit = add_vector(ray->pos, mult_coef(ray->dir, min_dist));
}

void		get_point_hit_cl(t_ray *ray, double min_dist, t_vec *p_hit)
{
	*p_hit = add_vector(ray->pos, mult_coef(ray->dir, min_dist));
}

t_vec		get_center_sph(const void *data)
{
	t_sph	sph;

	sph = (*(t_sph *)data);
	return (sph.pos);
}
