#include "../../inc/rtv1.h"

double      intersect_sphere(t_ray r, t_object *sphere)
{
    t_intersect     inter;

    inter.a = dot(r.dir, r.dir);
    inter.x = minus(r.origin, sphere->origin);
    inter.b = 2 * dot(r.dir, inter.x);
    inter.c = dot(inter.x, inter.x) - (sphere->raduis * sphere->raduis);
    inter.del = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.del < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.del)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.del)) / (2 * inter.a);
    if (inter.t1 >= 0 && inter.t1 < inter.t2)
        return (inter.t1);
    if (inter.t2 >= 0 && inter.t2 < inter.t1)
        return (inter.t2);
    return (-1);
}

double      intersect_plane(t_ray r, t_object *plane)
{
    t_intersect     inter;

    inter.x = minus(r.origin, plane->position);
    inter.a = dot(r.dir, plane->rotation);
    inter.b = dot(inter.x, plane->rotation);
    if (inter.a == 0 || (inter.a > 0 && inter.b > 0) || (inter.a < 0 && inter.b < 0))
        return (-1);
    inter.t1 = -inter.b / inter.a;
    if (inter.t1 < 0)
        return (-1);
    return (inter.t1);
}

double      intersect_cylinder(t_ray r, t_object *cylinder)
{
    t_intersect     inter;

    inter.a = dot(r.dir, r.dir) - (dot(r.dir, cylinder->rotation) * dot(r.dir, cylinder->rotation));
    inter.x = minus(r.origin, cylinder->position);
    inter.b = 2 * (dot(r.dir, inter.x) - (dot(r.dir, cylinder->position) * dot(r.dir, cylinder->rotation)));
    inter.c = dot(inter.x, inter.x) - (dot(inter.x, cylinder->rotation) * dot(inter.x, cylinder->rotation)) - (cylinder->raduis * cylinder->raduis);
    inter.del = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.del < 0)
        return (-1);
        inter.t1 = (-inter.b - sqrt(inter.del)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.del)) / (2 * inter.a);
    if (inter.t1 >= 0 && inter.t1 < inter.t2)
        return (inter.t1);
    if (inter.t2 >= 0 && inter.t2 < inter.t1)
        return (inter.t2);
    return (-1);
}

double      intersect_cone(t_ray r, t_object *cone)
{
    t_intersect     inter;

    inter.k = tan(cone->angle * 180.0/M_PI);
    inter.k = 1.0 * inter.k * inter.k;
    inter.a = dot(r.dir, r.dir) - inter.k * (dot(r.dir, cone->rotation) * dot(r.dir, cone->rotation));
    inter.x = minus(r.origin, cone->position);
    inter.b = 2 * (dot(r.dir, inter.x) - inter.k * (dot(inter.x, cone->position) * dot(inter.x, cone->position)));
    inter.c = dot(inter.x, inter.x) - inter.k * (dot(inter.x, cone->rotation) * dot(inter.x, cone->rotation));
    inter.del = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.del < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.del)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.del)) / (2 * inter.a);
    if (inter.t1 >= 0 && inter.t1 < inter.t2)
        return (inter.t1);
    if (inter.t2 >= 0 && inter.t2 < inter.t1)
        return (inter.t2);
    return (-1);
}

double      calc_intersect(t_ray r, t_object *object)
{
    if (object->type == 1)
        return (intersect_sphere(r, object));
    if (object->type == 0)
        return (intersect_plane(r, object));
    if (object->type == 2)
        return (intersect_cylinder(r, object));
    else
        return (intersect_cone(r, object));
    return (0.0);
}

t_object    *raycast_object(t_ray r, double *hit, t_scene *scene)
{
    t_object    *object;
    t_object    *tmp;
    double      het;

    object = scene->object;
    *hit = calc_intersect(r, object);
    tmp = object->next;
    while (tmp)
    {
        het = calc_intersect(r, tmp);
        if (het >= 0.0001 && (het < *hit || *hit == -1))
        {
            *hit = het;
            object = tmp;
        }
        tmp = tmp->next;
    }
    if (*hit >= 0.0001)
        return (object);
    return (NULL);
}

void ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
	int i;
	int j;
	t_ray r;
	double u, v;
	double hit;
	t_object *shp;

    r.origin.x = 0;
    r.origin.y = 0;
    r.origin.z = -1;	
	i = 0;
	while (i < WIDTH) 
	{
		j = 0;
		while (j < HEIGHT) 
		{
			shp = NULL;
			u = map(i , WIDTH, -1, 1);
			v = map(j , HEIGHT, 1, -1);
			r.dir.x = u;
			r.dir.y = v;
			r.dir.z = 1;
			r.dir = normalize(r.dir);
            shp = raycast_object(r, &hit, scene);
			if (shp)
				rtv->data[(WIDTH * j) + i] = 0xff0000;
			else
				rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}