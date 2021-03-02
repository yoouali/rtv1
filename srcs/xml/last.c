#include "../../inc/xml.h"

int     check_object_structer(t_object  *object)
{
    t_object    *tmp;

    tmp = object;
    while (tmp)
    {
        if (tmp->tab[0] == 0 || tmp->tab[1] == 0 || tmp->tab[5] == 0 || tmp->tab[4] == 0 || tmp->tab[6] == 0)
            return (0);
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
    if (xmlpar.scene->object)
        if (!check_object_structer(xmlpar.scene->object))
            return (0);
    return (1);
}