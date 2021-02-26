#include "xml.h"

int     get_camera_data(t_xml *xml, int rule_num, char *str)
{
    t_pos       pos;

    if ((rule_num == 8 && xml->scene->camera->tab[0] == 1) || (rule_num == 9 && xml->scene->camera->tab[1] == 1) ||\
    (rule_num == 19 && xml->scene->camera->tab[2] == 1) || (rule_num == 20 && xml->scene->camera->tab[3] == 1))
        return (0);
    if (rule_num == 19)
    {
        xml->scene->camera->tab[2] = 1;
        xml->scene->camera->fov = ft_atoi(str);
    }
    else
    {
        if (!get_pos(str, &pos))
            return (0);
        if (rule_num == 8)
        {
            xml->scene->camera->tab[0] = 1;
            xml->scene->camera->origin[0] = (double)pos.x;
            xml->scene->camera->origin[1] = (double)pos.y;
            xml->scene->camera->origin[2] = (double)pos.z;
        }
        if (rule_num == 9)
        {
            xml->scene->camera->tab[1] = 1;
            xml->scene->camera->lookat[0] = (double)pos.x;
            xml->scene->camera->lookat[1] = (double)pos.y;
            xml->scene->camera->lookat[2] = (double)pos.z;
        }
        if (rule_num == 20)
        {
            xml->scene->camera->tab[3] = 1;
            xml->scene->camera->up[0] = (double)pos.x;
            xml->scene->camera->up[1] = (double)pos.y;
            xml->scene->camera->up[2] = (double)pos.z;
        }
    }
    return (1);  
}

int     get_light_data(t_xml *xml, int rule_num, char *str)
{
    t_pos       pos;
    t_lgt       *lgt;

    lgt = xml->addr;
    if ((rule_num == 10 && lgt->tab[0] == 1) || (rule_num == 11 && lgt->tab[1] == 1) ||\
    (rule_num == 12 && lgt->tab[2] == 1))
        return (0);
    if (rule_num == 11)
    {
        lgt->tab[1] = 1;
        lgt->color = get_color(str);
    }
    if (rule_num == 12)
    {
        lgt->tab[2] = 1;
        lgt->intensity = ft_atoi(str);
    }
    if (rule_num == 10)
    {
        if (!get_pos(str, &pos))
                return (0);
        lgt->tab[0] = 1;
        lgt->position[0] = (double)pos.x;
        lgt->position[1] = (double)pos.y;
        lgt->position[2] = (double)pos.z;
    }
    return (1);  
}

char    *get_string_data(t_xml *xml)
{
    int     i;
    int     len;
    char    *str;

    len = 0;
    while (1)
    {
        len = 0;
         while (xml->line[xml->ind + len] &&  (xml->line[xml->ind + len] == ' ' || xml->line[xml->ind + len] == '\t'))
             len++;
        if (xml->line[xml->ind + len])
            break;
         if (!xml->line[xml->ind + len])
            get_line(xml, NULL);
    }
    len = 0;
    while (xml->line[xml->ind + len] && xml->line[xml->ind + len] != '<')
        len++;
    str = ft_strsub(xml->line, xml->ind, len);
    xml->ind = xml->ind + len;
    return (str);
}

int     read_data(t_xml *xml, int parent, int rule_num)
{
    char    *str;

    str = NULL;
    if (!(str = get_string_data(xml)))
        return (0);
    if (parent == 2)
        return (get_camera_data(xml, rule_num, str));
    if (parent == 3)
        return (get_light_data(xml, rule_num, str));
    if (parent > 3)
        return (get_object_data(xml, rule_num, str));
    return (1);
}