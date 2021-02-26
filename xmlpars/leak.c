#include "xml.h"

void        free_light(t_lgt *lgt)
{
    t_lgt   *tmp;
    while (lgt)
    {
        tmp = lgt;
        lgt = lgt->next;
        free(tmp);
    }
}

void        free_object(t_obj *obj)
{
    t_obj   *tmp;
    while (obj)
    {
        tmp = obj;
        obj = obj->next;
        free(tmp);
    }
}

t_scene     *leak_parr(t_xml *xml)
{
    if (xml->line)
        free(xml->line);
    if (xml->scene->camera)
        free(xml->scene->camera);
    if (xml->scene->light)
        free_light(xml->scene->light);
    if (xml->scene->object)
        free_object(xml->scene->object);
    free(xml->scene);
    return (NULL);
}