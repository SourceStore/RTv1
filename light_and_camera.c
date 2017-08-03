/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:31:25 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/02 18:44:58 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	change_dir_light(int keykode, t_scene *scene)
{
	if (keykode == 41 || keykode == 42)
		scene->head_l->loc_w.x += ((keykode == 41) ? -5 : 5);
	else if (keykode == 33 || keykode == 39)
		scene->head_l->loc_w.y += ((keykode == 33) ? 5 : -5);
}

void	change_focal_camera(int keykode, t_scene *scene)
{
	double	focus;

	focus = scene->cam->pos.z;
	scene->cam->pos.z = (keykode == 69 ? focus - 0.5 : focus + 0.5);
}

void	move_camera(int keykode, t_scene *scene)
{
	if (keykode == 125 || keykode == 126)
		scene->cam->pos.y += (keykode == 125 ? 0.5 : -0.5);
	if (keykode == 123 || keykode == 124)
		scene->cam->pos.x += (keykode == 123 ? 0.5 : -0.5);
}
