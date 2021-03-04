/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:05:37 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/04 11:29:26 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_vec3
{
	double x;
	double y;
	double z;
}				t_vec3;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}				t_ray;

typedef struct	s_camera
{
	int		tab[3];
	t_vec3	pos;
	t_vec3	dir;
	double	zoom;
}				t_camera;

typedef struct	s_light
{
	int		tab[3];
	t_vec3	pos;
	t_vec3	dir;
	double	intensity;
	t_vec3	color;
	struct s_light *next;
}				t_light;

typedef struct	s_object
{
	int		type;
	int		tab[7];
	t_vec3	position;
	t_vec3	orientation;
	t_vec3	translation;
	t_vec3	rotation;
	double	raduis;
	double	angle  ;
	t_vec3	color;
		struct	s_object *next;
}				t_object;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Event			event;
}						t_sdl;
typedef	struct			s_scene
{
	t_camera	*camera;
	t_light		*light;
	t_object	*object;
}						t_scene;

typedef struct			s_rtv1
{
	t_sdl				sdl;
	int					*data;
    int                 still_running;
}						t_rtv1;

typedef	struct		s_intersect
{
	double		a;
	double		b;
	double		c;
	double		k;
	double		t1;
	double		t2;
	t_vec3		x;
	double		delta;
}					t_intersect;

typedef	struct 		s_hsno
{
	double		hit;
	t_vec3		surface_normal;
	t_object	*object;
	t_light		*light;
	t_vec3		h;
	double		difcoef;
	double		specoef;
	double		ambcoef;
	t_vec3		l_dir;
	t_vec3		sh;
}					t_hsno;


#include "xml.h"

int			sdl_init_texture(t_rtv1	*rtv);
int         sdl_init_render(t_rtv1   *rtv);
int			sdl_init_win(t_rtv1	*rtv);

void		process_input(t_rtv1 *rtv);

double	map(int position, int max_wh, double new_min_scope
		, double new_max_scope);

void cast_rays(t_rtv1 *rtv, char *file);

double		vec_length(t_vec3 vec);
t_vec3		plus(t_vec3 a, t_vec3 b);
t_vec3		minus(t_vec3 a, t_vec3 b);
t_vec3		mult(t_vec3 a, t_vec3 b);
t_vec3		mult2(double t, t_vec3 b);
t_vec3		divide(t_vec3 b, double t);
double		dot(t_vec3    a, t_vec3 b);
t_vec3		cross(t_vec3 a, t_vec3 b);
t_vec3		normalize(t_vec3 vec);

//multi object and light
void ft_cast_rays(t_rtv1 *rtv, t_scene *scene);
t_object    *raycast_object(t_ray r, t_hsno *hsno, t_scene *scene);
double      calc_intersect(t_ray r, t_object *object);
double      intersect_cone(t_ray r, t_object *cone);
double      intersect_cylinder(t_ray r, t_object *cylinder);
double      intersect_plane(t_ray r, t_object *plane);
double      intersect_sphere(t_ray r, t_object *sphere);
int     ft_get_full_color(t_hsno *hsno, t_light *light, t_scene *scene, t_ray *ray);
double      ft_get_specular(t_hsno *hsno, t_light *light);
double     ft_get_diffuse(t_hsno *hsno, t_light *light);


// To be deleted

#endif
