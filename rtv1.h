/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishchen <rishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 20:10:30 by rishchen          #+#    #+#             */
/*   Updated: 2017/08/03 20:25:59 by rishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdio.h>
# include "get_next_line.h"
# include "unistd.h"
# include "stdlib.h"
# include "mlx.h"
# include <math.h>

# define EPS 1e-5
# define H 600
# define W 600
# define T 200

# define ANGLE(angle) ((angle * M_PI) / 180)
# define SQR(x) ((x) * (x))
# define MIN(x, y) ((x) < (y) ? (x) : (y))

# define SPH "sphere"
# define CON "cone"
# define PLA "plane"
# define CYL "cyl"
# define RAY "ray"
# define CAM "camera"
# define TRUE 1
# define FALSE 0

typedef struct		s_solor
{
	double			b;
	double			g;
	double			r;
	double			o;
}					t_col;

typedef struct		s_3dvector
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct		s_lsrc
{
	t_vec			loc_w;
	t_vec			location;
	t_vec			dir;
	t_vec			nv;
	double			t;
	t_col			color;
	struct s_lsrc	*next;
}					t_light;

typedef struct		s_ray
{
	t_vec			pos;
	t_vec			vec;
	t_vec			dir;
	t_col			col;
	double			t;
}					t_ray;

typedef struct		s_camera
{
	t_vec			pos;
	t_vec			dir_r;
	t_vec			uv;
	double			focus;
}					t_cam;

typedef struct		s_anti_multiple_alloc
{
	int				f_sph;
	int				f_pl;
	int				f_con;
	int				f_cyl;
	int				f_cam;
	int				f_l_s;

}					t_checker;

typedef struct		s_sphere
{
	t_vec			pos;
	t_col			col;
	t_col			cols;
	t_vec			nv;
	double			r;
}					t_sph;

typedef	struct		s_plane
{
	t_vec			dot_0;
	t_col			col;
	t_vec			nv;
	t_vec			uv;
}					t_pl;

typedef	struct		s_cylinder
{
	t_vec			dot_0;
	t_col			col;
	t_vec			nv;
	t_vec			uv;
	double			r;
	double			m;
	double			h;
}					t_cyl;

typedef	struct		s_conus
{
	t_vec			dot_0;
	t_col			col;
	t_vec			nv;
	t_vec			uv;
	double			angle;
}					t_con;

/*
** Object dynamic method dispatch
*/

typedef struct		s_object
{
	void			*data;
	double			(*intersect)(const void *data, t_ray *ray,
									double *t_0, double *t_1);
	void			(*get_hit_point)(t_ray *ray, double min_dist, t_vec *p_hit);
	t_vec			(*get_norm_vec)(const void *data, t_ray *ray,
										t_vec p_hit, double min_dist);
	t_col			(*get_color)(const void *data);
	t_vec			(*get_center)(const void *data);
	struct s_object	*next;
}					t_obj;

typedef	struct		s_scene
{
	void			*mlx;
	void			*img;
	void			*win;
	char			*addr;
	int				bpp;
	int				sl;
	int				endian;
	int				count_obj;
	t_obj			*obj;
	t_obj			*o_inter;
	t_light			*lght;
	t_ray			*ray;
	t_obj			*head_o;
	t_obj			*last;
	t_light			*head_l;
	t_light			*light;
	t_cam			*cam;
	t_checker		*f_alloc;
	int				flag;
	double			u;
	double			v;
	t_vec			p_o_s;
	t_vec			r_dir;
	t_vec			p_hit;
	t_vec			n_hit;
	double			min_dist;
	double			t_0;
	double			t_1;
	double			image_asp_ratio;
	double			scale;
	t_ray			raytl;
	t_ray			rayty;
	double			lambert;
	t_col			spec;
	t_col			col_buff;
	t_col			final_color;
	t_vec			h;
}					t_scene;

void				core_point_check(int ac, char **av, t_scene *scene);
int					distribution_func(char **str, t_scene *scene);
void				correct_param_obj(char **str, t_scene **scene);
void				correct_type_data(char **str, t_scene **scene);
void				correct_type_data_p2(char **str, t_scene **scene);
void				alloc_scene(char **str, t_scene **scene);
void				push_back_obj(t_scene **scene, t_obj *obj);
void				add_obj(t_scene **scene, t_obj *obj);

t_vec				init_vec(double x, double y, double z);
t_col				init_col(int b, int g, int r, int o);
t_col				init_col_al(int b, int g, int r, int o);
t_vec				unit_vec(t_vec vec);
double				len_vect(t_vec vec);
int					len_matrix(char **str);
t_vec				mult_coef(t_vec vec1, double coef);
t_vec				margin_vectors(t_vec vec1, t_vec vec2);
t_vec				add_vector(t_vec vec1, t_vec vec2);
double				dot_product(t_vec t_vec1, t_vec t_vec2);

void				intersect_cam_ray_with_objects(t_scene *scene,
													int x, int y);

void				change_dir_light(int keykode, t_scene *scene);
void				change_focal_camera(int keykode, t_scene *scene);

void				alloc_sphere(char **str, t_scene **scene);
t_col				get_color_sphere(const void *data);
double				intersect_sphere(const void *data, t_ray *ray,
										double *t_0, double *t_1);
t_vec				get_center_sph(const void *data);
void				get_point_hit_s(t_ray *ray, double min_dist, t_vec *p_hit);
t_vec				get_norm_vector_s(const void *data, t_ray *ray,
										t_vec p_hit, double min_dist);
t_obj				*init_sphere(t_sph *sph);
int					return_value_sphere(double *t_0, double *t_1, t_ray *ray);

void				alloc_plane(char **str, t_scene **scene);
t_col				get_color_plane(const void *data);
double				intersect_plane(const void *data, t_ray *ray,
										double *t_0, double *t_1);
void				get_point_hit_p(t_ray *ray, double min_dist, t_vec *p_hit);
t_vec				get_norm_vector_p(const void *data, t_ray *ray,
										t_vec p_hit, double min_dist);
t_obj				*init_plane(t_pl *pl);

void				alloc_cyl(char **str, t_scene **scene);
t_col				get_color_cyl(const void *data);
double				intersect_cyl(const void *data, t_ray *ray,
										double *t_0, double *t_1);
void				get_point_hit_cl(t_ray *ray, double min_dist, t_vec *p_hit);
t_vec				get_norm_vector_cl(const void *data, t_ray *ray,
										t_vec p_hit, double min_dist);
t_obj				*init_cylinder(t_cyl *cyl);
int					return_value_cylinder(double *t_0, double *t_1, t_ray *ray);

void				alloc_conus(char **str, t_scene **scene);
t_col				get_color_conus(const void *data);
double				intersect_conus(const void *data, t_ray *ray,
										double *t_0, double *t_1);
void				get_point_hit_cn(t_ray *ray, double min_dist, t_vec *p_hit);
t_vec				get_norm_vector_cn(const void *data, t_ray *ray,
										t_vec p_hit, double min_dist);
t_obj				*init_conus(t_con *con);
int					return_value_cone(double *t_0, double *t_1, t_ray *ray);

void				alloc_camera(char **str, t_scene **scene);

void				alloc_light_source(char **str, t_scene **scene);

void				start_point(t_scene *scene);
t_vec				find_pos_on_scr(t_scene *scene);
void				init_ray(t_scene *scene, double x, double y);
void				init_ray_to_light(t_scene *scene, t_light *light);
void				algorithm_blinn_lambert(t_scene *scene);
t_col				traced_color(t_scene *scene, t_light *light);

void				ft_swap(double *param1, double *param2);
int					exit_win(void *param);
int					close_win(int keykode);
int					len_matrix(char **str);
double				len_vect(t_vec vec);
t_vec				init_vec(double x, double y, double z);
t_col				init_col(int b, int g, int r, int o);
t_col				init_col_al(int b, int g, int r, int o);
void				move_camera(int keykode, t_scene *scene);
int					set_functions(int keykode, t_scene **scene);
t_col				mult_col(t_col col, double k);
void				clamp(t_col *color);
void				ft_put_pixel(t_scene *scene, double x,
									double y, t_col color);
void				color_mixing(t_scene *scene);
void				loop_point(t_scene *scene);
t_scene				*init_scene(void);
int					check_num(char **str);
void				del_buf(char **str);
void				len_str(char **str);
#endif
