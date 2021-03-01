#include "../../inc/rtv1.h"

double intersect_sphere(t_ray r, t_object *sphere)
{
    t_intersect inter;

    inter.a = dot(r.dir, r.dir);
    inter.x = minus(r.origin, sphere->origin);
    inter.b = 2 * dot(r.dir, inter.x);
    inter.c = dot(inter.x, inter.x) - (sphere->raduis * sphere->raduis);
    inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.delta < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
    if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
        return (inter.t2);
    return (-1);
}

double intersect_plane(t_ray r, t_object *plane)
{
    t_intersect inter;

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

double intersect_cylinder(t_ray r, t_object *cylinder)
{
    t_intersect inter;

    inter.a = dot(r.dir, r.dir) - (dot(r.dir, cylinder->rotation) * dot(r.dir, cylinder->rotation));
    inter.x = minus(r.origin, cylinder->origin);
    inter.b = 2 * (dot(r.dir, inter.x) - (dot(r.dir, cylinder->rotation) * dot(inter.x, cylinder->rotation)));
    inter.c = dot(inter.x, inter.x) - (dot(inter.x, cylinder->rotation) * dot(inter.x, cylinder->rotation)) - (cylinder->raduis * cylinder->raduis);
    inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.delta < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
    if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
        return (inter.t2);
    return (-1);
}

double intersect_cone(t_ray r, t_object *cone)
{
    t_intersect inter;

    inter.k = tan(cone->angle * 180.0 / M_PI);
    inter.k = 1.0 + inter.k * inter.k;
    inter.a = dot(r.dir, r.dir) - inter.k * (dot(r.dir, cone->rotation) * dot(r.dir, cone->rotation));
    inter.x = minus(r.origin, cone->origin);
    inter.b = 2 * (dot(r.dir, inter.x) - inter.k * (dot(r.dir, cone->rotation) * dot(inter.x, cone->rotation)));
    inter.c = dot(inter.x, inter.x) - inter.k * (dot(inter.x, cone->rotation) * dot(inter.x, cone->rotation));
    inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
    if (inter.delta < 0)
        return (-1);
    inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
    inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
    if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) || (inter.t1 >= 0.0 && inter.t2 < 0.0))
        return (inter.t1);
    if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) || (inter.t2 >= 0.0 && inter.t1 < 0.0))
        return (inter.t2);
    return (-1);
}

double calc_intersect(t_ray r, t_object *object)
{
    if (object->type == 0)
        return (intersect_plane(r, object));
    if (object->type == 1)
        return (intersect_sphere(r, object));
    if (object->type == 2)
        return (intersect_cylinder(r, object));
    else
        return (intersect_cone(r, object));
    return (0.0);
}

void calc_surface_normal(t_ray r, t_object *object, t_hsno *hsno)
{
    double m;
    double k;

    hsno->h = plus(r.origin, mult2(hsno->hit, r.dir));
    if (object->type == 0)
    {
        if (dot(r.dir, object->rotation) < 0)
            hsno->surface_normal = minus((t_vec3){0, 0, 0}, object->rotation);
        else
            hsno->surface_normal = object->rotation;
    }
    if (object->type == 1)
        hsno->surface_normal = normalize(minus(hsno->h, object->origin));
    if (object->type == 2)
    {
        m = dot(r.dir, mult2(hsno->hit, object->rotation)) + dot(minus(r.origin, object->origin), object->rotation);
        hsno->surface_normal = normalize(minus(minus(hsno->h, object->origin), mult2(m, object->rotation)));
    }
    if (object->type == 3)
    {
        k = tan(object->angle * 180 / M_PI);
        k = 1.0 + k * k;
        m = dot(r.dir, mult2(hsno->hit, object->rotation)) + dot(minus(r.origin, object->origin), object->rotation);
        hsno->surface_normal = normalize(minus(minus(hsno->h, object->origin), mult2(k, mult2(m, object->rotation))));
    }
}

t_object *raycast_object(t_ray r, t_hsno *hsno, t_scene *scene)
{
    t_object *object;
    t_object *tmp;
    double het;

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
    calc_surface_normal(r, object, hsno);
    return (object);
}

double ft_get_diffuse(t_hsno *hsno, t_light *light)
{
    t_vec3 ldir;
    double diffuse_coef;

    ldir = normalize(minus(light->pos, hsno->h));
    diffuse_coef = dot(ldir, hsno->surface_normal);
    if (diffuse_coef < 0)
        diffuse_coef = 0;
    return (diffuse_coef);
}

double ft_get_specular(t_hsno *hsno, t_light *light)
{
    t_vec3 ldir;
    double specular_coef;
    t_vec3 reflect;

    hsno->l_dir = normalize(minus(hsno->h, light->pos));
    ldir = hsno->l_dir;
    reflect = normalize(minus(mult2(2.0 * dot(hsno->surface_normal, ldir), hsno->surface_normal), ldir));
    specular_coef = powf(fabs(dot(hsno->surface_normal, reflect) > 0 ? 0 : dot(hsno->surface_normal, reflect)), 120);
    return (specular_coef);
}

int shadow(t_ray *r, t_hsno *hsno, t_light *l, t_object *objects)
{
    t_ray shadow_ray;
    double dis_light;
    double hit;
    t_vec3 old_hit;
    t_object *tmp;

    shadow_ray.origin = l->pos;
    shadow_ray.dir = hsno->l_dir;
    old_hit = plus(r->origin, mult2(hsno->hit, r->dir));
    dis_light = sqrt(dot(minus(l->pos, old_hit), minus(l->pos, old_hit)));
    tmp = objects;
    while (tmp)
    {
        if (tmp != hsno->object)
        {
            hit = calc_intersect(shadow_ray, tmp);
            if (hit >= 0.0001 && (dis_light > hit && dis_light - hit > 0.0001))
                return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int ft_get_full_color(t_hsno *hsno, t_light *light, t_scene *scene, t_ray *ray)
{
    int color;
    int r;
    int g;
    int b;
    int sh;
    double intensity;

    hsno->ambcoef = 0.1;
    hsno->specoef = 0;
    hsno->difcoef = 0;
    hsno->light = light;
    r = hsno->object->color.x * hsno->ambcoef;
    if (r > 255)
        r = 255;
    g = hsno->object->color.y * hsno->ambcoef;
    if (g > 255)
        g = 255;
    b = hsno->object->color.z * hsno->ambcoef;
    if (b > 255)
        b = 255;
    while (hsno->light)
    {
        intensity = map(hsno->light->intensity, 100, 0, 1);
        hsno->difcoef = ft_get_diffuse(hsno, hsno->light) * intensity;
        hsno->specoef = ft_get_specular(hsno, hsno->light) * intensity;
        sh = shadow(ray, hsno, hsno->light, scene->object);
        r += (int)(hsno->object->color.x * hsno->difcoef + hsno->light->color.x * hsno->specoef) * sh;
        if (r > 255)
            r = 255;
        g += (int)(hsno->object->color.y * hsno->difcoef + hsno->light->color.y * hsno->specoef) * sh;
        if (g > 255)
            g = 255;
        b += (int)(hsno->object->color.z * hsno->difcoef + hsno->light->color.z * hsno->specoef) * sh;
        if (b > 255)
            b = 255;
        hsno->light = hsno->light->next;
    }
    color = (r << 16 | g << 8 | b);
    return (color);
}

void ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
    int i;
    int j;
    t_ray r;
    double u, v;
    t_hsno hsno;

    r.origin.x = scene->camera->pos.x + 0.0005;
    r.origin.y = scene->camera->pos.y;
    r.origin.z = scene->camera->pos.z;
    i = 0;
    t_vec3 wv = normalize(minus(scene->camera->dir, scene->camera->pos));
    t_vec3 uv = cross((t_vec3){0.005, 1, 0}, wv);
    t_vec3 vv = cross(wv, uv);
    double h = tanf((scene->camera->zoom * M_PI / 180.0) / 2);
    double w = (double)(WIDTH / HEIGHT) * h;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            hsno.object = NULL;
            u = map(i, WIDTH, -1, 1) * w;
            v = map(j, HEIGHT, 1, -1) * h;
            r.dir = plus(wv, plus(mult2(v, vv), mult2(u, uv)));
            r.dir = normalize(r.dir);
            hsno.object = raycast_object(r, &hsno, scene);
            if (hsno.object)
            {
                if (scene->light)
                    rtv->data[(WIDTH * j) + i] = ft_get_full_color(&hsno, scene->light, scene, &r);
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