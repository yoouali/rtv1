#include "xml.h"

void    set_object(t_obj *obj, int rule_num)
{
    int     i;

    obj->type = rule_num - 4;
    i = -1;
    while (++i < 9)
        obj->tab[i] = 0;
    if (rule_num == 4)
    {
        obj->tab[0] = 1;
        obj->tab[5] = 1;
    }
    if (rule_num > 4)
        obj->tab[1] = 1;
    if (rule_num == 5)
        obj->tab[3] = 1;
    if (rule_num == 7)
        obj->tab[5] = 1;
    if (rule_num != 7)
        obj->tab[4] = 1;
}

int     get_object_data(t_xml *xml, int rule_num, char *str)
{
    t_obj   *obj;
    t_pos   pos;

    obj = xml->addr;
    if ((rule_num == 8 && obj->tab[0] == 1) || (rule_num == 10 && obj->tab[1] == 1) || (rule_num == 11 && obj->tab[2] == 1) || (rule_num == 13 && obj->tab[3] == 1) || (rule_num == 14 && obj->tab[4] == 1) ||\
    (rule_num == 15 && obj->tab[5] == 1) || (rule_num == 16 && obj->tab[6] == 1) || (rule_num == 17 && obj->tab[7] == 1) || (rule_num == 18 && obj->tab[8] == 1))
        return (0);
    if (rule_num == 10 || rule_num == 13 || rule_num == 8)
        if (!(get_pos(str, &pos)))
            return (0);
    if (rule_num == 11)
    {
        obj->tab[2] = 1;
        obj->color = get_color(str);
    }
    else if (rule_num == 15)
    {
        obj->tab[5] = 1;
        obj->radius = (double)ft_atoi(str);
    }
    else if (rule_num == 16)
    {
        obj->tab[6] = 1;
        obj->diffuse = ft_atoi(str);
    }
    else if (rule_num == 17)
    {
        obj->tab[7] = 1;
        obj->ambient = ft_atoi(str);
    }
    else if (rule_num == 18)
    {
        obj->tab[8] = 1;
        obj->specular = ft_atoi(str);
    }
    else if (rule_num == 8)
    {
        obj->tab[0] = 1;
        obj->origin[0] = (double)pos.x;
        obj->origin[1] = (double)pos.y;
        obj->origin[2] = (double)pos.z;
    }
    else if (rule_num == 10)
    {
        obj->tab[1] = 1;
        obj->position[0] = (double)pos.x;
        obj->position[1] = (double)pos.y;
        obj->position[2] = (double)pos.z;
    }
    else if (rule_num == 13)
    {
        obj->tab[3] = 1;
        obj->rotation[0] = (double)pos.x;
        obj->rotation[1] = (double)pos.y;
        obj->rotation[2] = (double)pos.z;
    }
    else if (rule_num == 14)
    {
        obj->tab[4] = 1;
        obj->angle = (double)ft_atoi(str);
    }
    return (1);
}