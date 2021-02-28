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
    if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
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
    inter.x = minus(r.origin, cylinder->origin);
    inter.b = 2 * (dot(r.dir, inter.x) - (dot(r.dir, cylinder->rotation) * dot(inter.x, cylinder->rotation)));
    inter.c = dot(inter.x, inter.x) - (dot(inter.x, cylinder->rotation) * dot(inter.x, cylinder->rotation)) - (cylinder->raduis * cylinder->raduis);
    inter.del = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.del < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.del)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.del)) / (2 * inter.a);
   if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
        return (inter.t2);
    return (-1);
}

double      intersect_cone(t_ray r, t_object *cone)
{
    t_intersect     inter;

    inter.k = tan(cone->angle * 180.0/M_PI);
    inter.k = 1.0 + inter.k * inter.k;
    inter.a = dot(r.dir, r.dir) - inter.k * (dot(r.dir, cone->rotation) * dot(r.dir, cone->rotation));
    inter.x = minus(r.origin, cone->origin);
    inter.b = 2 * (dot(r.dir, inter.x) - inter.k * (dot(r.dir, cone->rotation) * dot(inter.x, cone->rotation)));
    inter.c = dot(inter.x, inter.x) - inter.k * (dot(inter.x, cone->rotation) * dot(inter.x, cone->rotation));
    inter.del = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.del < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.del)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.del)) / (2 * inter.a);
   if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
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

void     calc_surface_normale(t_ray r, t_object *object, t_hsno *hsno)
{
    double      m;
    double      k;

    hsno->h = plus(r.origin, mult2(hsno->hit, r.dir));
    if (object->type == 1)
        hsno->surface_normale = normalize(minus(hsno->h, object->origin));
    if (object->type == 2)
    {
        m = dot(r.dir, mult2(hsno->hit, object->rotation)) + dot(minus(r.origin, object->origin), object->rotation);
        hsno->surface_normale = normalize(minus(minus(hsno->h, object->origin), mult2(m, object->rotation)));
    }
    if (object->type == 3)
    {
        k = tan(object->angle * 180 / M_PI);
        k = 1.0 + k * k;
        m = dot(r.dir, mult2(hsno->hit, object->rotation)) + dot(minus(r.origin, object->origin), object->rotation);
        hsno->surface_normale = normalize(minus(minus(hsno->h, object->origin), mult2(k, mult2(m, object->rotation))));
    }
}

t_object    *raycast_object(t_ray r, t_hsno *hsno, t_scene *scene)
{
    t_object    *object;
    t_object    *tmp;
    double      het;

    object = scene->object;
    hsno->hit = calc_intersect(r, object);
    tmp = object->next;
    while (tmp)
    {
        het = calc_intersect(r, tmp);
        
        if (het >= 0.0001 && (het < hsno->hit || hsno->hit == -1))
        {
            hsno->hit = het;
            object = tmp;
        }
        tmp = tmp->next;
    }
    if (hsno->hit < 0.0001)
        return (NULL);
    calc_surface_normale(r, object, hsno);
    return (object);
}

double     ft_get_diffuse(t_hsno *hsno, t_light *light)
{
    t_vec3  ldir;
    double  diffuse_coef;

    ldir = normalize(minus(light->pos, hsno->h));
    diffuse_coef = dot(ldir, hsno->surface_normale);
    if (diffuse_coef < 0)
        diffuse_coef = 0;
    return (diffuse_coef);
}

double      ft_get_specular(t_hsno *hsno, t_light *light)
{
    t_vec3  ldir;
    double  specular_coef;
    t_vec3  reflect;

    ldir = normalize(minus(hsno->h, light->pos));
    reflect = normalize(minus(mult2(2.0 * dot(hsno->surface_normale, ldir), hsno->surface_normale), ldir));
    specular_coef = powf(fabs(dot(hsno->surface_normale, reflect) > 0 ? 0 : dot(hsno->surface_normale, reflect)), 500) /2;
    return (specular_coef);
}

int     ft_get_full_color(t_hsno *hsno, t_light *light)
{
    int     color;
    int     r;
    int     g;
    int     b;

    hsno->ambcoef = 0.1;
    hsno->specoef = 0;
    hsno->difcoef = 0;
    hsno->light = light;
    while (hsno->light)
    {
        hsno->difcoef += ft_get_diffuse(hsno, hsno->light);
        hsno->specoef += ft_get_specular(hsno, hsno->light);
        hsno->light = hsno->light->next;
    }
    r = ((int)hsno->object->color.x * hsno->ambcoef + hsno->object->color.x * hsno->difcoef  + 255 * hsno->specoef);
    if (r > 255)
        r = 255;
    g = ((int)hsno->object->color.y * hsno->ambcoef + hsno->object->color.y * hsno->difcoef  + 255 * hsno->specoef);
    if (g > 255)
        g = 255;
    b = ((int)hsno->object->color.z * hsno->ambcoef + hsno->object->color.z * hsno->difcoef  + 255 *  hsno->specoef);
    if (b > 255)
        b = 255;
    color = (r << 16 | g << 8 | b);
    return (color);
}

void ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
	int i;
	int j;
	t_ray r;
	double u, v;
    t_hsno  hsno;

    r.origin.y = 0;
    r.origin.y = 0;
    r.origin.z = -1;	
	i = 0;
	while (i < WIDTH) 
	{
		j = 0;
		while (j < HEIGHT) 
		{
			hsno.object = NULL;
			u = map(i , WIDTH, -1, 1);
			v = map(j , HEIGHT, 1, -1);
			r.dir.x = u;
			r.dir.y = v;
			r.dir.z = 1;
			r.dir = normalize(r.dir);
            hsno.object = raycast_object(r, &hsno, scene);
			if (hsno.object)
            {
                if (scene->light)
				    rtv->data[(WIDTH * j) + i] = ft_get_full_color(&hsno, scene->light);
                else
                    rtv->data[(WIDTH * j) + i] = ((int)(hsno.object->color.x) << 16 | (int)(hsno.object->color.y) << 8 | (int)(hsno.object->color.z));
            }
			else
				rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}