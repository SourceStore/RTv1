/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:21:48 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/02 18:45:21 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		margin_vectors(t_vec vec1, t_vec vec2)
{
	t_vec	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}

t_vec		add_vector(t_vec vec1, t_vec vec2)
{
	t_vec	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

double		dot_product(t_vec t_vec1, t_vec t_vec2)
{
	return (t_vec1.x * t_vec2.x + t_vec1.y * t_vec2.y + t_vec1.z * t_vec2.z);
}

t_vec		unit_vec(t_vec vec)
{
	t_vec		uv;
	double		len;

	len = len_vect(vec);
	uv.x = vec.x / len;
	uv.y = vec.y / len;
	uv.z = vec.z / len;
	return (uv);
}

t_vec		mult_coef(t_vec vec1, double coef)
{
	t_vec	res;

	res.x = vec1.x * coef;
	res.y = vec1.y * coef;
	res.z = vec1.z * coef;
	return (res);
}
