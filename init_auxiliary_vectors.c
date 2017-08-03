/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_auxiliary_vectors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:49:12 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 18:20:46 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		push_back_obj(t_scene **scene, t_obj *obj)
{
	((*scene)->last)->next = obj;
	((*scene)->last) = ((*scene)->last)->next;
}

t_vec		init_vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_col		init_col(int b, int g, int r, int o)
{
	t_col	col;

	col.b = b;
	col.g = g;
	col.r = r;
	col.o = o;
	return (col);
}

t_col		init_col_al(int b, int g, int r, int o)
{
	t_col	col;

	col.b = (double)b / 255;
	col.g = (double)g / 255;
	col.r = (double)r / 255;
	col.o = (double)o / 255;
	return (col);
}

void		init_ray(t_scene *scene, double x, double y)
{
	scene->ray->pos = scene->cam->pos;
	scene->ray->dir = init_vec(x, y, 1);
	scene->ray->dir = unit_vec(scene->ray->dir);
	scene->ray->t = 1000000;
}
