/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:34:46 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/24 18:47:35 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_vec3  calc_surf_normal(t_object *o, t_ray *r, double hit)
{
	t_vec3	surface_normal;
    double  m;

    if (o->type == 1) //sphere
    {
        o->h = plus(r->origin, mult2(hit,r->dir));
	    surface_normal = normalize(minus(o->h, o->position));
    }
    else if (o->type == 2) //cylindre
    {
        o->h = plus(r->origin, mult2(hit,r->dir));
	    m = dot(r->dir, mult2(hit, o->rotation)) + dot(minus(r->origin, o->position), o->rotation);
	    surface_normal = normalize(minus(minus(o->h, o->position), mult2(m, o->rotation)));
    }
    return (surface_normal);
}

double	get_diffuse(t_ray *r, double hit, t_object *o, t_light *l)
{
	double	diffuse_coef;
    t_vec3	surface_normal;

	surface_normal = calc_surf_normal(o, r, hit);
	l->dir = normalize(minus(l->pos, o->h));
	diffuse_coef = dot(l->dir, surface_normal);
	if (diffuse_coef < 0)
		diffuse_coef = 0;

	return (diffuse_coef);
}

double	get_specular(t_ray *r, double hit, t_object *o, t_light *l)
{
	t_vec3	reflect;
	double	specular_coef;
    t_vec3	surface_normal;

	surface_normal = calc_surf_normal(o, r, hit);
	l->dir = normalize(minus(o->h, l->pos));
	reflect =  normalize(minus(mult2(2.0 * dot(surface_normal, l->dir), surface_normal), l->dir));
	specular_coef = powf(dot(surface_normal, reflect), 100);

	return (specular_coef);
}

int	get_full_color(t_ray *ray, double hit, t_object *o, t_light *l)
{
	int color;
	int r;
	int g;
	int b;

	l->dif_coef = get_diffuse(ray, hit, o, l);
	l->spe_coef = get_specular(ray, hit, o, l);
	r = ((int)(o->color.x * l->amb_coef + o->color.x * l->dif_coef + (o->color.x + l->color.x) * l->spe_coef));
	if (r > 255)
		r = 255;
	g = ((int)(o->color.y * l->amb_coef + o->color.y * l->dif_coef + (o->color.y + l->color.y) * l->spe_coef));
	if (g > 255)
		g = 255;
	b = (int)(o->color.z * l->amb_coef + o->color.z * l->dif_coef + (o->color.z + l->color.z) * l->spe_coef);
	if (b > 255)
		b = 255;
	color = (r << 16 | g << 8 | b);
	return (color);
}