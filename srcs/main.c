/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/26 16:28:46 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double	map(int position, int max_wh, double new_min_scope
		, double new_max_scope)
{
	double range;

	range = new_max_scope - new_min_scope;
	return (new_min_scope + position * (range / max_wh));
}


/*svoid setup_scene(t_ray *r, t_sphere *sphere, t_light *l)
{
	r->origin.x = 0;
	r->origin.y = 0;
	r->origin.z = -1;
	
	sphere->pos.x = 0;
	sphere->pos.y = 0;
	sphere->pos.z = 1;
	sphere->r = 0.9;
	sphere->color.x = 255;
	sphere->color.y = 16;
	sphere->color.z = 256;
	l->pos.x = 0;
	l->pos.y = 6;
	l->pos.z = -10;

	l->color.x = 255;
	l->color.z = 255;
	l->color.y = 255;
}*/

t_sphere *setup_scene(t_ray *r, t_light *l, char *file)
{
	t_scene	*scene;

	scene = xml_parsser(file);
	// if (!scene)
	// 	printf("lhrba\n");
	// else
	// 	printf("lhrba2\n");
    r->origin.x = 0;
    r->origin.y = 0;
    r->origin.z = -1;
	
    t_sphere *sphere;
    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    sphere->pos.x = 0.2;
    sphere->pos.y = 0;
    sphere->pos.z = 0;
    sphere->r = 0.2;
    sphere->color.x = 255;
    sphere->color.y = 0;
    sphere->color.z = 0;
    sphere->next = NULL;
    
	t_sphere *tmp;
    tmp = (t_sphere *)malloc(sizeof(t_sphere));
    tmp->pos.x = 0;
    tmp->pos.y = 0;
    tmp->pos.z = 0;
    tmp->r = 0.2;
    tmp->color.x = 0;
    tmp->color.y = 255;
    tmp->color.z = 255;

    tmp->next = NULL;
    sphere->next = tmp;
	tmp->next = (t_sphere *)malloc(sizeof(t_sphere));
	tmp = tmp->next;
    tmp->pos.x = -0.2;
    tmp->pos.y = 0;
    tmp->pos.z = 0;
    tmp->r = 0.2;
    tmp->color.x = 0;
    tmp->color.y = 255;
    tmp->color.z = 0;
	tmp->next = NULL;

    l->pos.x = 0.9;
    l->pos.y = 0;
    l->pos.z = 0;
    l->color.x = 255;
    l->color.z = 255;
    l->color.y = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	
	t_light *head;
	head = l;
	l->next = (t_light *)malloc(sizeof(t_light));
	l = l->next;
	l->pos.x = 0;
    l->pos.y = -1;
    l->pos.z = -1;
    l->color.x = 255;
    l->color.y = 255;
    l->color.z = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	l = head;

	return (sphere);
}

t_cylinder *setup_scene2(t_ray *r, t_light *l, char *file)
{
	t_scene	*scene;

	r->origin.x = 0;
    r->origin.y = 0;
    r->origin.z = -1;
	scene = xml_parsser(file);

	l->pos.x = 0.9;
    l->pos.y = 0;
    l->pos.z = 0;
    l->color.x = 255;
    l->color.z = 255;
    l->color.y = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	
	t_light *head;
	head = l;
	l->next = (t_light *)malloc(sizeof(t_light));
	l = l->next;
	l->pos.x = 0;
    l->pos.y = -1;
    l->pos.z = -1;
    l->color.x = 255;
    l->color.y = 255;
    l->color.z = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	l = head;

	t_cylinder *c;
    c = (t_cylinder *)malloc(sizeof(t_cylinder));
    c->pos.x = 0;
    c->pos.y = 0;
    c->pos.z = 2;
    c->r = 0.2;
    c->color.x = 255;
    c->color.y = 0;
    c->color.z = 0;
    c->rot.x = 0;
    c->rot.y = 1;
    c->rot.z = 0;
    c->next = NULL;

    t_cylinder *head1;
    head1 = c;
    c->next = (t_cylinder *)malloc(sizeof(t_cylinder));
    c = c->next;
    c->pos.x = 0;
    c->pos.y = 5;
    c->pos.z = 0;
    c->r = 0.2;
    c->color.x = 0;
    c->color.y = 255;
    c->color.z = 0;
    c->rot.x = 0;
    c->rot.y = 1;
    c->rot.z = 0;
    c->next = NULL;
    c = head1;
	return (c);
}

t_cone *setup_scene3(t_ray *r, t_light *l, char *file)
{
	t_scene	*scene;

	r->origin.x = 0;
    r->origin.y = 0;
    r->origin.z = -1;
	scene = xml_parsser(file);

	l->pos.x = -1;
    l->pos.y = 0;
    l->pos.z = -1;
    l->color.x = 255;
    l->color.z = 255;
    l->color.y = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	
	// t_light *head;
	// head = l;
	// l->next = (t_light *)malloc(sizeof(t_light));
	// l = l->next;
	// l->pos.x = 0;
    // l->pos.y = -1;
    // l->pos.z = -1;
    // l->color.x = 255;
    // l->color.y = 255;
    // l->color.z = 255;
	// l->amb_coef = 0.1;
	// l->next = NULL;
	// l = head;

	t_cone *c;
    c = (t_cone *)malloc(sizeof(t_cone));
    c->pos.x = 0;
    c->pos.y = 0;
    c->pos.z = 5;
    c->color.x = 255;
    c->color.y = 0;
    c->color.z = 0;
    c->a = 10;
    c->rot.x = 0;
    c->rot.y = 1;
    c->rot.z = 0;
    c->next = NULL;

    // t_cone *head1;
    // head1 = c;
    // c->next = (t_cone *)malloc(sizeof(t_cone));
    // c = c->next;
    // c->pos.x = 0;
    // c->pos.y = 5;
    // c->pos.z = 0;
    // c->color.x = 0;
    // c->color.y = 255;
    // c->color.z = 0;
    // c->a = 10;
    // c->rot.x = 0;
    // c->rot.y = 1;
    // c->rot.z = 0;
    // c->next = NULL;
    // c = head1;
	return (c);
}

t_plane *setup_scene4(t_ray *r, t_light *l, char *file)
{
	t_scene	*scene;

	r->origin.x = 0;
    r->origin.y = 0;
    r->origin.z = -1;
	scene = xml_parsser(file);

	l->pos.x = -1;
    l->pos.y = 0;
    l->pos.z = -1;
    l->color.x = 255;
    l->color.z = 255;
    l->color.y = 255;
	l->amb_coef = 0.1;
	l->next = NULL;
	
	// t_light *head;
	// head = l;
	// l->next = (t_light *)malloc(sizeof(t_light));
	// l = l->next;
	// l->pos.x = 0;
    // l->pos.y = -1;
    // l->pos.z = -1;
    // l->color.x = 255;
    // l->color.y = 255;
    // l->color.z = 255;
	// l->amb_coef = 0.1;
	// l->next = NULL;
	// l = head;

	t_plane *c;
    c = (t_plane *)malloc(sizeof(t_plane));
    c->pos.x = 0;
    c->pos.y = 0;
    c->pos.z = 0;
    c->color.x = 255;
    c->color.y = 0;
    c->color.z = 0;
    c->a = 10;
    c->rot.x = 1;
    c->rot.y = 1;
    c->rot.z = 2;
    c->next = NULL;

    // t_plane *head1;
    // head1 = c;
    // c->next = (t_plane *)malloc(sizeof(t_plane));
    // c = c->next;
    // c->pos.x = 0;
    // c->pos.y = 5;
    // c->pos.z = 0;
    // c->color.x = 0;
    // c->color.y = 255;
    // c->color.z = 0;
    // c->a = 10;
    // c->rot.x = 0;
    // c->rot.y = 1;
    // c->rot.z = 0;
    // c->next = NULL;
    // c = head1;
	return (c);
}

int main(int ac, char **av)
{
	t_rtv1 *rtv;
    t_scene *scene;

	ac = 0;
    scene = NULL;
	rtv = malloc(sizeof(t_rtv1));
	rtv->still_running = sdl_init_win(rtv);
	rtv->data = malloc(sizeof(int) * (WIDTH * HEIGHT));
    if (!(scene = xml_parsser(av[1])))
        return (0);
   /* t_scene *tmp;
    tmp = scene;
    if (scene)
    {
        printf("camera :\n");
        printf("origin : x:%d | y:%d | z:%d\n", (int)scene->camera->pos.x, (int)scene->camera->pos.y, (int)scene->camera->pos.z);
        printf("lookat : x:%d | y:%d | z:%d\n", (int)scene->camera->dir.x, (int)scene->camera->dir.y, (int)scene->camera->dir.z);
        printf("zoom : %f\n", scene->camera->zoom);
        if (scene->light)
        {
            while (scene->light)
            {
                printf("position : x:%d | y:%d | z:%d\n", (int)scene->light->pos.x, (int)scene->light->pos.y, (int)scene->light->pos.z);
                printf("intensity : %f\n", scene->light->intensity);
                printf("color : %f | %f | %f\n", scene->light->color.x, scene->light->color.y, scene->light->color.z);
                scene->light = scene->light->next;
            }
        }
        if (scene->object)
        {
            while (scene->object)
            {
                printf("the type : %d\n", scene->object->type);
                if (scene->object->type > 0)
                    printf("origin : x:%d | y:%d | z:%d\n", (int)scene->object->origin.x, (int)scene->object->origin.y, (int)scene->object->origin.z);
                if (scene->object->type == 0)
                    printf("position : x:%d | y:%d | z:%d\n", (int)scene->object->position.x, (int)scene->object->position.y, (int)scene->object->position.z);
                if (scene->object->type != 1)
                    printf("rotation : x:%d | y:%d | z:%d\n", (int)scene->object->rotation.x, (int)scene->object->rotation.y, (int)scene->object->rotation.z);
                if (scene->object->type == 1 || scene->object->type == 2)
                    printf("radius : %d\n", (int)scene->object->raduis);
                if (scene->object->type == 3)
                    printf("angle : %d\n", (int)scene->object->angle);
                printf("color : | %f | %f | %f\n", scene->object->color.x, scene->object->color.y, scene->object->color.z);
                printf("diffuse : %f\n", scene->object->diffuse);
                printf("ambient : %f\n", scene->object->ambient);
                printf("specular : %f\n", scene->object->specular);
                printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\llll|\n");
                scene->object = scene->object->next;
            }
        }
    }
    printf("hfjkdhsfkhdskf\n");*/
	while (rtv->still_running == 0)
	{
		ft_cast_rays(rtv, scene);
		SDL_UpdateTexture(rtv->sdl.texture, NULL, rtv->data, HEIGHT * sizeof(int));
		SDL_RenderCopy(rtv->sdl.renderer, rtv->sdl.texture, NULL, NULL);
		process_input(rtv);
		SDL_RenderPresent(rtv->sdl.renderer);
	}
	return (0);
}
