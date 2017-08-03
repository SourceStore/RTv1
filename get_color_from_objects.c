/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_from_objects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 18:09:10 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 18:10:28 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_col		get_color_conus(const void *data)
{
	t_con	cone;

	cone = (*(t_con*)data);
	return (cone.col);
}

t_col		get_color_sphere(const void *data)
{
	t_sph	sph;

	sph = (*(t_sph *)data);
	return (sph.col);
}

t_col		get_color_plane(const void *data)
{
	t_pl	pla;

	pla = *(t_pl*)data;
	return (pla.col);
}

t_col		get_color_cyl(const void *data)
{
	t_cyl	cyl;

	cyl = (*(t_cyl*)data);
	return (cyl.col);
}
