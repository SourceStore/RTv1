/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 20:22:19 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:26:05 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		alloc_camera(char **str, t_scene **scene)
{
	if (len_matrix(str) != 7)
		exit(write(1, "Invalid data!\n", 14));
	len_str(str);
	(*scene)->cam = (t_cam *)malloc(sizeof(t_cam));
	(*scene)->cam->pos = init_vec(ft_atoi(str[0]),
			ft_atoi(str[1]), ft_atoi(str[2]));
	(*scene)->cam->dir_r = init_vec(ft_atoi(str[3]),
			ft_atoi(str[4]), ft_atoi(str[5]));
	(*scene)->cam->uv = unit_vec((*scene)->cam->dir_r);
	(*scene)->cam->focus = ft_atoi(str[6]);
}
