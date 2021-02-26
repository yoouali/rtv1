#include "xml.h"

int     check_light(t_lgt *lgt)
{
    t_lgt   *tmp;

    tmp = lgt;
    while (tmp)
    {
        if (!tmp->tab[0] || !tmp->tab[1] || !tmp->tab[2])
            return (0);
        tmp = tmp->next;
    }
    return (1);
}
int     check_object(t_obj *obj)
{
    t_obj   *tmp;
    int     i;

    tmp = obj;
    while (tmp)
    {
        i = -1;
        while (++i < 9)
            if (!tmp->tab[i])
                return (0);
        tmp = tmp->next;
    }
    return (1);
}

int     last_check(t_xml *xml)
{
    if (!xml->scene->camera)
        return (0);
    if (xml->scene->light)
        if (!check_light(xml->scene->light))
            return (0);
    if (xml->scene->object)
        if (!check_object(xml->scene->object))
            return (0);
    return (1);
}