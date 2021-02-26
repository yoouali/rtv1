#include "xml.h"

void        *load_lgt(t_xml *xml)
{
    t_lgt   *tmp;

    if (!xml->scene->light)
    {
        if (!(xml->scene->light = (t_lgt *)malloc(sizeof(t_lgt))))
            return (NULL);
        xml->scene->light->tab[0] = 0;
        xml->scene->light->tab[1] = 0;
        xml->scene->light->tab[2] = 0;
        xml->scene->light->next = NULL;
        return (xml->scene->light);
    }
    tmp = xml->scene->light;
    while (tmp->next)
        tmp = tmp->next;
    if (!(tmp->next = (t_lgt *)malloc(sizeof(t_lgt))))
        return (NULL);
    tmp->next->tab[0] = 0;
    tmp->next->tab[1] = 0;
    tmp->next->tab[2] = 0;
    tmp->next->next = NULL;
    return (tmp->next);
}

void        *load_obj(t_xml *xml, int rule_num)
{
    t_obj   *tmp;
    t_obj   *obj;


    if (!xml->scene->object)
    {
        if (!(xml->scene->object = (t_obj *)malloc(sizeof(t_obj))))
            return (NULL);
        obj = xml->scene->object;
    }
    else
    {
        tmp = xml->scene->object;
        while (tmp->next)
            tmp = tmp->next;
        if (!(tmp->next = (t_obj *)malloc(sizeof(t_obj))))
            return (NULL);
        obj = tmp->next;
    }
    set_object(obj, rule_num);
    obj->next = NULL;
    obj->type = rule_num;
    return (obj);
}


void        *load_rule(t_xml *xml, int rule_num)
{
    if (rule_num == 2)
    {
        if (xml->scene->camera)
            return (NULL);
        if (!(xml->scene->camera = (t_cam *)malloc(sizeof(t_cam))))
            return (NULL);
        xml->scene->camera->tab[0] = 0;
        xml->scene->camera->tab[1] = 0;
        xml->scene->camera->tab[2] = 0;
        xml->scene->camera->tab[3] = 0;
        return (xml->scene->camera);
    }
    if (rule_num == 3)
        return (load_lgt(xml));
    return (load_obj(xml, rule_num));
}