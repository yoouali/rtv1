#include "../../inc/xml.h"

void    *load_light(t_scene *scene)
{
    t_light     *light;
    t_light     *tmp;

    light = NULL;
    if (!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->tab[0] = 0;
    light->tab[1] = 0;
    light->tab[2] = 0;
    light->next = NULL;
    if (!scene->light)
        scene->light = light;
    else
    {
        tmp = scene->light;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = light;
    }
    return (light);
}

void    *load_object(t_scene *scene, int rule_num)
{
    t_object    *object;
    t_object    *tmp;

    object = NULL;
    if (!(object = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    object->next = NULL;
    if (!scene->object)
        scene->object = object;
    else
    {
        tmp = scene->object;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = object;
    }
    set_object(object, rule_num);
    return (object);
}

void    *load_rule(t_scene *scene, int rule_num)
{
    if (rule_num == 2)
    {
        if (scene->camera)
            return (NULL);
        if (!(scene->camera = (t_camera *)malloc(sizeof(t_camera))))
            return (NULL);
        scene->camera->tab[0] = 0;
        scene->camera->tab[1] = 0;
        scene->camera->tab[2] = 0;
        return (scene->camera);
    }
    if (rule_num == 3)
        return (load_light(scene));
    return (load_object(scene, rule_num));
}