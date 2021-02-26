#include "../../inc/xml.h"

int     check_light_structer(t_light *light)
{
    t_light *tmp;
    int     i;

    tmp = light;
    while (tmp)
    {
        i = 0;
        while (i < 3)
        {
            if (tmp->tab[i] != 1)
                return (0);
            i++;
        }
        tmp = tmp->next;
    }
    return (1);
}

int     check_object_structer(t_object *object)
{
    t_object    *tmp;
    int         i;

    tmp = object;
    while (tmp)
    {
        i = 0;
        while(i < 9)
        {
            if (tmp->tab[i] != 1)
                return (0);
            i++;
        }
        tmp = tmp->next;
    }
    return (1);
}

int     structer_check(t_xmlpar xmlpar)
{
    int     i;

    if (!xmlpar.scene->camera)
        return (0);
    i = 0;
    while (i < 3)
    {
        if (xmlpar.scene->camera->tab[i] != 1)
            return (0);
        i++;
    }
    if (xmlpar.scene->light)
        if (!check_light_structer(xmlpar.scene->light))
            return (0);
    if (xmlpar.scene->object)
        if (!check_object_structer(xmlpar.scene->object))
            return (0);
    return (1);
}