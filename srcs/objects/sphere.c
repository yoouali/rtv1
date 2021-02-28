/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:27:57 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/28 14:13:57 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"


/*
**
** We need a vector representing the distance between the start of 
** the ray and the position of the circle.
** This is the term (p0 - c) 
**
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

double  intersect(t_ray *r, t_sphere *s)
{
    double A, B, C, discr;
    t_vec3 destenation;
    double t1, t2;

    A = dot(r->dir, r->dir);
    destenation = minus(r->origin, s->pos);
    B = 2 * dot(r->dir, destenation);
    C = dot(destenation, destenation) - (s->r * s->r);
    discr = B * B - (4 * A * C);
    if (discr < 0)
        return (-1);
    else
    {
        t1 = (-B - sqrt(discr)) / (2 * A);
        t2 = (-B + sqrt(discr)) / (2 * A);
		if (t1 >= 0 && t1 < t2)
			return (t1);
		if (t2 >= 0 && t2 < t1)
			return (t2);
		return (-1);
    }
}

double	get_diffuse(t_ray *r, double hit, t_sphere *sphere, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	double	diffuse_coef;

	h = plus(r->origin, mult2(hit,r->dir));
	surface_normal = normalize(minus(h, sphere->pos));
	l->dir = normalize(minus(l->pos, h));
	diffuse_coef = dot(l->dir, surface_normal);
	if (diffuse_coef < 0)
		diffuse_coef = 0;

	return (diffuse_coef);
}

/*
** r = −l + 2(n•l)n
*/

double	get_specular(t_ray *r, double hit, t_sphere *sphere, t_light *l)
{
	t_vec3	h;
	t_vec3	surface_normal;
	t_vec3	reflect;
	double	specular_coef;

	h = plus(r->origin, mult2(hit,r->dir));
	surface_normal = normalize(minus(h, sphere->pos));
	l->dir = normalize(minus(h, l->pos));
	reflect =  normalize(minus(mult2(2.0 * dot(surface_normal, l->dir), surface_normal), l->dir));
	specular_coef = powf(dot(surface_normal, reflect), 100);

	return (specular_coef);
}



int	get_full_color(t_ray *ray, double hit, t_sphere *sphere, t_light *l)
{
	int color;
	int r;
	int g;
	int b;

	l->dif_coef = get_diffuse(ray, hit, sphere, l);
	l->spe_coef = get_specular(ray, hit, sphere, l);
	r = ((int)(sphere->color.x * l->amb_coef + sphere->color.x * l->dif_coef + l->color.x * l->spe_coef));
	if (r > 255)
		r = 255;
	g = ((int)(sphere->color.y * l->amb_coef + sphere->color.y * l->dif_coef + l->color.y * l->spe_coef));
	if (g > 255)
		g = 255;
	b = (int)(sphere->color.z * l->amb_coef + sphere->color.z * l->dif_coef + l->color.z * l->spe_coef);
	if (b > 255)
		b = 255;
	color = (r << 16 | g << 8 | b);
	return (color);
}

void cast_rays(t_rtv1 *rtv, char *file)
{
	int i;
	int j;
	t_ray r;
	double u, v;
	double hit;
	double het;
	t_sphere *shp;
	t_sphere *tmp;
	t_sphere *sphere;
	t_light l;

	sphere = setup_scene(&r,&l, file);
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
			hit = intersect(&r, tmp);
			if (hit >= 0.001)
				shp = tmp;
			tmp = tmp->next;
			while (tmp)
			{
				het = intersect(&r, tmp);
				if (het >= 0.0001 && (hit > het || hit == -1))
				{
					hit = het;
					shp = tmp;
				}
				tmp = tmp->next;
			}
			if (shp)
				rtv->data[(WIDTH * j) + i] = get_full_color(&r, hit, shp, &l);
			else
				rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}