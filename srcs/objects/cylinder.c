/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:23:50 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/25 18:08:22 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/**
** This is tems of cords
**
** equation of a shpere is: x^2 + y^2 + z^2 = R^2
** which means the same distance from the origin of the cam to the hit point to the power of 2 ( name "P" )
** and it will give us P^2 = R^2
**
** But in terms of vectors
** this is the equation of the c in vectors
** The hit point is in (P - C)^2 = R^2
** 
*/

/*double  intersect_cylinder(t_ray *r, t_cylinder *s)
{
   double A, B, C, delta;
    t_vec3 destenation;
    double t1;
	double t2;

	A = dot(r->dir, r->dir) - (dot(r->dir, s->rot) * dot(r->dir, s->rot));
	destenation = minus(r->origin, s->pos);
	B = 2 * (dot(r->dir, destenation) - (dot(r->dir, s->rot) * dot(destenation, s->rot)));
	C = dot(destenation, destenation) - (dot(destenation, s->rot) * dot(destenation, s->rot)) - (s->r * s->r);
    delta = B * B - (4 * A * C);
    if (delta < 0)
        return (-1);
    else
    {
        t1 = (-B - sqrt(delta)) / (2 * A);
        t2 = (-B + sqrt(delta)) / (2 * A);
		if ((t1 <= t2 && t1 >= 0.0) || (t1 >= 0.0 && t2 < 0.0))
			return (t1);
		if ((t2 <= t1 && t2 >= 0.0) || (t2 >= 0.0 && t1 < 0.0))
			return (t2);
		return (-1);
    }
}*/

/*
**	v = c->rot
*/
/*
double	get_diffuse2(t_ray *r, double hit, t_cylinder *c, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	double	diffuse_coef;
	double	m;

	h = plus(r->origin, mult2(hit,r->dir));
	m = dot(r->dir, mult2(hit, c->rot)) + dot(minus(r->origin, c->pos), c->rot);
	surface_normal = normalize(minus(minus(h, c->pos), mult2(m, c->rot)));
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
/*
double	get_specular2(t_ray *r, double hit, t_cylinder *c, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	t_vec3	reflect;
	double	specular_coef;
	double m;

	h = plus(r->origin, mult2(hit,r->dir));
	m = dot(r->dir, mult2(hit, c->rot)) + dot(minus(r->origin, c->pos), c->rot);
	surface_normal = normalize(minus(minus(h, c->pos), mult2(m, c->rot)));
	l->dir = normalize(minus(h, l->pos));	
	reflect =  normalize(minus(mult2(2.0 * dot(surface_normal, l->dir), surface_normal), l->dir));
	specular_coef = powf(fabs(dot(surface_normal, reflect) > 0 ? 0 : dot(surface_normal, reflect)), 500) / 2;

	return (specular_coef);
}

void		get_coef2(t_ray *r, double hit, t_cylinder *c, t_light *l)
{
	l->dif_coef = 0;
	l->spe_coef = 0;
    l->amb_coef = 0.1;
	while (l != NULL)
	{
		l->dif_coef += get_diffuse2(r, hit, c, l);
		l->spe_coef += get_specular2(r, hit, c, l);
		l = l->next;
	}
}

int	get_full_color2(t_cylinder *c, t_light *l)
{
	int color;
	int r;
	int g;
	int b;

	r = (int)(c->color.x * l->amb_coef + c->color.x * l->dif_coef + (c->color.x + l->color.x) * l->spe_coef);
	if (r > 255)
		r = 255;
	g = (int)(c->color.y * l->amb_coef + c->color.y * l->dif_coef + (c->color.y + l->color.y) * l->spe_coef);
	if (g > 255)
		g = 255;
	b = (int)(c->color.z * l->amb_coef + c->color.z * l->dif_coef + (c->color.z + l->color.z) * l->spe_coef);
	if (b > 255)
		b = 255;
	color = (r << 16 | g << 8 | b);
	return (color);
}

// Re-do the multi-objects

void cast_rays2(t_rtv1 *rtv, char *file)
{
	int i;
	int j;
	t_cylinder *c;
	t_ray r;
	double u, v;
	double hit;
	double het;
	t_cylinder *shp;
	t_cylinder *tmp;
	t_light *l;

	l = (t_light *)malloc(sizeof(t_light));
	c = setup_scene2(&r, l, file);
	i = 0;
	while (i < WIDTH) 
	{
		j = 0;
		while (j < HEIGHT) 
		{
			tmp = c;
			shp = NULL;
			het = 0.0;
			hit = 0.0;
			u = map(i , WIDTH, -1, 1);
			v = map(j , HEIGHT, 1, -1);
			r.dir.x = u;
			r.dir.y = v;
			r.dir.z = 1;
			r.dir = normalize(r.dir);
			//hit = intersect_cylinder(&r, tmp);
			if (hit >= 0.001)
				shp = tmp;
			tmp = tmp->next;
			while (tmp)
			{
			//	het = intersect_cylinder(r, tmp);
				if (het >= 0.0001 && (hit > het || hit == -1))
				{
					hit = het;
					shp = tmp;
				}
				tmp = tmp->next;
			}
            if (shp)
            {
				get_coef2(&r, hit, shp, l);
                rtv->data[(WIDTH * j) + i] = get_full_color2(shp, l);
            }
            else
                rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}*/