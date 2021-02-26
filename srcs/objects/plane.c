/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/25 16:00:54 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** This is tems of cords
**
** equation of a shpere is: x^2 + y^2 + z^2 = R^2
** which means the same distance from the origin of the cam to the hit point to the power of 2 ( name "P" )
** and it will give us P^2 = R^2
**
** But in terms of vectors
** this is the equation of the sphere in vectors
** The hit point is in (P - C)^2 = R^2
** 
*/

double  intersect_plane(t_ray *r, t_plane *p)
{
    t_vec3 destenation;
    double t;

	destenation = minus(r->origin, p->pos);
	if (dot(r->dir, p->rot) == 0)
		return (-1);
	if ((dot(r->dir, p->rot) > 0 && dot(destenation, p->rot) > 0) || (dot(r->dir, p->rot) < 0 && dot(destenation, p->rot) < 0))
		return (-1);
	t = -dot( destenation, p->rot) / dot(r->dir, p->rot);
	if (t < 0)
		return (-1);
	return (t);
}

double	get_diffuse4(t_ray *r, double hit, t_plane *p, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	double	diffuse_coef;

	h = plus(r->origin, mult2(hit,r->dir));
	if (dot(r->dir, p->rot) < 0)
		surface_normal = minus((t_vec3){0,0,0}, p->rot);
	else
		surface_normal = p->rot;//normalize(minus(h, sphere->pos));
	l->dir = normalize(minus(l->pos, h));
	diffuse_coef = dot(l->dir, surface_normal);
	if (diffuse_coef < 0)
		diffuse_coef = 0;

	return (diffuse_coef);
}

/*
**
** r = −l + 2(n • l)n
**
*/

double	get_specular4(t_ray *r, double hit, t_plane *p, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	t_vec3	reflect;
	double	specular_coef;
	// double m;

	h = plus(r->origin, mult2(hit,r->dir));
	if (dot(r->dir, p->rot) < 0)
		surface_normal = minus((t_vec3){0,0,0}, p->rot);
	else
		surface_normal = p->rot;
	// surface_normal = normalize(minus(h, sphere->pos));
	// m = dot(r->dir, mult2(hit, sphere->rot)) + dot(minus(r->origin, sphere->pos), sphere->rot);
	// surface_normal = normalize(minus(minus(h, sphere->pos), mult2(m, sphere->rot)));
	l->dir = normalize(minus(h, l->pos));	
	reflect =  normalize(minus(mult2(2.0 * dot(surface_normal, l->dir), surface_normal), l->dir));
	specular_coef = powf(fabs(dot(surface_normal, reflect) > 0 ? 0 : dot(surface_normal, reflect)), 500);

	return (specular_coef);
}

void		get_coef4(t_ray *r, double hit, t_plane *p, t_light *l)
{
	l->dif_coef = 0;
	l->spe_coef = 0;
    l->amb_coef = 0.1;
	while (l != NULL)
	{
		l->dif_coef += get_diffuse4(r, hit, p, l);
		l->spe_coef += get_specular4(r, hit, p, l);
		l = l->next;
	}
}

int	get_full_color4(t_plane *sphere, t_light *l)
{
	int color;
	int r;
	int g;
	int b;

	r = (int)(sphere->color.x * l->amb_coef + sphere->color.x * l->dif_coef + (sphere->color.x + l->color.x) * l->spe_coef);
	if (r > 255)
		r = 255;
	g = (int)(sphere->color.y * l->amb_coef + sphere->color.y * l->dif_coef + (sphere->color.y + l->color.y) * l->spe_coef);
	if (g > 255)
		g = 255;
	b = (int)(sphere->color.z * l->amb_coef + sphere->color.z * l->dif_coef + (sphere->color.z + l->color.z) * l->spe_coef);
	if (b > 255)
		b = 255;
	color = (r << 16 | g << 8 | b);
	return (color);
}

void cast_rays4(t_rtv1 *rtv, char *file)
{
	int i;
	int j;
	t_plane *sphere;
	t_ray r;
	double u, v;
	double hit;
	//double het;
	t_plane *shp;
	t_plane *tmp;
	t_light *l;

	l = (t_light *)malloc(sizeof(t_light));
	sphere = setup_scene4(&r, l, file);
	i = 0;
	while (i < WIDTH) 
	{
		j = 0;
		while (j < HEIGHT) 
		{
			tmp = sphere;
			shp = NULL;
			u = map(i , WIDTH, -1, 1);
			v = map(j , HEIGHT, 1, -1);
			r.dir.x = u;
			r.dir.y = v;
			r.dir.z = 1;
			r.dir = normalize(r.dir);
			hit = intersect_plane(&r, tmp);
			if (hit >= 0.001)
                shp = tmp;
            /*tmp = tmp->next;
            while (tmp)
            {
                het = intersect(&r, tmp);
                if (het >= 0.0001 && (hit > het || hit == -1))
                {
                    hit = het;
                    shp = tmp;
                }
                tmp = tmp->next;
            }*/
            // if (shp)
            // {
			// 	get_coef4(&r, hit, shp, l);
            //     rtv->data[(WIDTH * j) + i] = get_full_color4(shp, l);
			// 	//rtv->data[(WIDTH * j) + i] = 0xff;
            // }
            // else
            //     rtv->data[(WIDTH * j) + i] = 0;
			if (shp)
				rtv->data[(WIDTH * j) + i] = 0xFF0000;
			else
				rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}