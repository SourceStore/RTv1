/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:40:46 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:44:51 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_light_source(char **str, t_scene **scene)
{
	t_light	*lght;
	t_light	*light;

	if (len_matrix(str) != 6)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	lght = (t_light *)malloc(sizeof(t_light));
	lght->loc_w = init_vec(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	lght->dir = init_vec(ft_atoi(str[3]), ft_atoi(str[4]), ft_atoi(str[5]));
	lght->nv = unit_vec(lght->dir);
	lght->t = 2000;
	lght->next = NULL;
	if ((*scene)->head_l == NULL)
		(*scene)->head_l = lght;
	else
	{
		light = (*scene)->head_l;
		while (light->next)
			light = light->next;
		light->next = lght;
	}
}
