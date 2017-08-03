/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 20:39:49 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:46:37 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		correct_type_data(char **str, t_scene **scene)
{
	if (ft_strcmp(str[0], SPH) == 0)
	{
		(*scene)->flag = 0;
		if ((*scene)->f_alloc->f_sph != 0)
			exit((int)write(1, &"Invalid data file for sphere!\n", 30));
		(*scene)->f_alloc->f_sph = 1;
	}
	else if (ft_strcmp(str[0], PLA) == 0)
	{
		if ((*scene)->f_alloc->f_pl != 0)
			exit((int)write(1, &"Invalid data file for plane!\n", 29));
		(*scene)->flag = 1;
		(*scene)->f_alloc->f_pl = 1;
	}
	else if (ft_strcmp(str[0], CYL) == 0)
	{
		if ((*scene)->f_alloc->f_cyl != 0)
			exit((int)write(1, &"Invalid data file for cylinder!\n", 32));
		(*scene)->flag = 2;
		(*scene)->f_alloc->f_cyl = 1;
	}
	else
		correct_type_data_p2(str, scene);
}

void		correct_type_data_p2(char **str, t_scene **scene)
{
	if (ft_strcmp(str[0], CON) == 0)
	{
		if ((*scene)->f_alloc->f_con != 0)
			exit((int)write(1, &"Invalid data file for conus!\n", 29));
		(*scene)->flag = 3;
		(*scene)->f_alloc->f_con = 1;
	}
	else if (ft_strcmp(str[0], CAM) == 0)
	{
		if ((*scene)->f_alloc->f_cam != 0)
			exit((int)write(1, &"Invalid data file for camera!\n", 30));
		(*scene)->flag = 4;
		(*scene)->f_alloc->f_cam = 1;
	}
	else if (ft_strcmp(str[0], RAY) == 0)
	{
		if ((*scene)->f_alloc->f_l_s != 0)
			exit((int)write(1, &"Invalid data file for ray!\n", 27));
		(*scene)->flag = 5;
		(*scene)->f_alloc->f_l_s = 1;
	}
}

void		alloc_scene(char **str, t_scene **scene)
{
	if ((*scene)->flag == 0)
		alloc_sphere(str, scene);
	else if ((*scene)->flag == 1)
		alloc_plane(str, scene);
	else if ((*scene)->flag == 2)
		alloc_cyl(str, scene);
	else if ((*scene)->flag == 3)
		alloc_conus(str, scene);
	else if ((*scene)->flag == 4)
		alloc_camera(str, scene);
	else if ((*scene)->flag == 5)
		alloc_light_source(str, scene);
}

void		correct_param_obj(char **str, t_scene **scene)
{
	char	*s;
	t_obj	*p;

	s = str[0];
	if ((ft_strcmp(s, CAM) || ft_strcmp(s, CON) || ft_strcmp(s, CYL) ||
			ft_strcmp(s, PLA) || ft_strcmp(s, RAY) || ft_strcmp(s, SPH)) &&
				!check_num(str))
		correct_type_data(str, scene);
	else
		alloc_scene(str, scene);
	if (ft_strcmp(str[0], RAY) == 0)
	{
		p = ((*scene)->head_o);
		while (p)
			p = p->next;
	}
}

/*
** name_obj count \n center or base position,BGRO, radius or axuliary value
*/

void		core_point_check(int ac, char **av, t_scene *scene)
{
	int		fd;
	char	*str;
	char	**buf_str;

	fd = open(av[ac - 1], O_RDONLY);
	if (fd < 0)
		exit((int)write(1, "Invalid file name!\n", 19));
	while (get_next_line(fd, &str) > 0)
	{
		if (str == NULL)
			exit(1);
		buf_str = ft_strsplit(str, '\t');
		if (buf_str == NULL || buf_str[0] == NULL)
			exit((int)write(1, "Invalid data!\n", 14));
		correct_param_obj(buf_str, &scene);
		del_buf(buf_str);
		ft_strdel(buf_str);
		ft_strdel(&str);
	}
}
