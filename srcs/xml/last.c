#include "../../inc/xml.h"

void    vectorse_rotation(t_object *object)
{
    t_vec3          vec;
    double          alpha;


    if (object->rotation.x != 0)
    {
        alpha = object->rotation.x * (M_PI / 180.0);
        vec.x = object->orientation.x;
        vec.y = object->orientation.y * cos(alpha) + object->orientation.z * sin(alpha);
        vec.z = -object->orientation.y * sin(alpha) + object->orientation.z * cos(alpha);
        object->orientation = vec;
    }
    if (object->rotation.y != 0)
    {
        alpha = object->rotation.y * (M_PI / 180.0);
        vec.y = object->orientation.y;
        vec.x = object->orientation.x * cos(alpha) + object->orientation.z * sin(alpha);
        vec.z = -object->orientation.x * sin(alpha) + object->orientation.z * cos(alpha);
        object->orientation = vec;
    }
    if (object->rotation.z != 0)
    {
        alpha = object->rotation.z * (M_PI / 180.0);
        vec.z = object->orientation.z;
        vec.x = object->orientation.x * cos(alpha) - object->orientation.y * sin(alpha);
        vec.y = object->orientation.x * sin(alpha) + object->orientation.y * cos(alpha);
        object->orientation = vec;
    }
}

int     check_object_structer(t_object  *object)
{
    t_object    *tmp;

    tmp = object;
    while (tmp)
    {
        if (tmp->tab[0] == 0 || tmp->tab[1] == 0 || tmp->tab[5] == 0 || tmp->tab[4] == 0 || tmp->tab[6] == 0)
            return (0);
        if (tmp->tab[2] == 1)
            tmp->position = plus(tmp->position, tmp->translation);
        if (tmp->tab[3] == 1)
            vectorse_rotation(tmp);
        tmp = tmp->next;
    }
    return (1);
}

int     check_light_structer(t_light  *light)
{
    t_light     *tmp;

    tmp = light;
    while (tmp)
    {
        if (tmp->tab[0] == 0 || tmp->tab[1] == 0 || tmp->tab[2] == 0)
            return (0);
        tmp = tmp->next;
    }
    return (1);
}

int     structer_check(t_xmlpar xmlpar)
{
    t_camera    *camera;
    t_light     *light;

    if (!xmlpar.scene->camera)
        return (0);
    camera = xmlpar.scene->camera;
    light = xmlpar.scene->light;
    if (camera->tab[0] == 0 || camera->tab[1] == 0 || camera->tab[2] == 0)
        return (0);
    if (xmlpar.scene->light)
        if (!check_light_structer(xmlpar.scene->light))
            return (0);
    if (xmlpar.scene->object)
        if (!check_object_structer(xmlpar.scene->object))
            return (0);
    return (1);
}