#include "../../inc/xml.h"

void    set_object(t_object *object, int rule_num)
{
    int     i;

    object->type = rule_num - 4;
    i = -1;
    while (++i < 9)
        object->tab[i] = 0;
    if (rule_num == 4)
    {
        object->tab[0] = 1;
        object->tab[5] = 1;
    }
    if (rule_num > 4)
        object->tab[1] = 1;
    if (rule_num == 5)
        object->tab[3] = 1;
    if (rule_num == 7)
        object->tab[5] = 1;
    if (rule_num != 7)
        object->tab[4] = 1;
}

int     get_object_data(t_xmlpar *xmlpar, int rule_num, char *str)
{
    t_object    *object;
    t_vec3      vec3;
    int         color;

    object = (t_object *)xmlpar->addr;
    if ((rule_num == 8 && object->tab[0] == 1) || (rule_num == 10 && object->tab[1] == 1) || (rule_num == 11 && object->tab[2] == 1) || (rule_num == 13 && object->tab[3] == 1) || (rule_num == 14 && object->tab[4] == 1) ||\
    (rule_num == 15 && object->tab[5] == 1) || (rule_num == 16 && object->tab[6] == 1) || (rule_num == 17 && object->tab[7] == 1) || (rule_num == 18 && object->tab[8] == 1))
        return (0);
    if (rule_num == 10 || rule_num == 13 || rule_num == 8)
        if (!get_pos(str, &vec3))
            return (0);
    if (rule_num == 11)
    {
        color = get_color_data(str);
        object->color.x = (color >> 16) & 255;
        object->color.y = (color >> 8) & 255;
        object->color.z = color & 255;
        object->tab[2] = 1;
    }
    else if (rule_num == 15)
    {
        object->tab[5] = 1;
        object->raduis = (double)ft_atoi(str);
    }
    else if (rule_num == 16)
    {
        object->tab[6] = 1;
        object->diffuse = (double)ft_atoi(str);
    }
    else if (rule_num == 17)
    {
        object->tab[7] = 1;
        object->ambient = (double)ft_atoi(str);
    }
    else if (rule_num == 18)
    {
        object->tab[8] = 1;
        object->specular = (double)ft_atoi(str);
    }
    else if (rule_num == 8)
    {
        object->tab[0] = 1;
        object->origin.x = vec3.x;
        object->origin.y = vec3.y;
        object->origin.z = vec3.z;
    }
    else if (rule_num == 10)
    {
        object->tab[1] = 1;
        object->position.x = vec3.x;
        object->position.y = vec3.y;
        object->position.z = vec3.z;
    }
    else if (rule_num == 13)
    {
        object->tab[3] = 1;
        object->rotation.x = vec3.x;
        object->rotation.y = vec3.y;
        object->rotation.z = vec3.z;
        object->rotation = normalize(object->rotation);
    }
    else if (rule_num == 14)
    {
        object->tab[4] = 1;
        object->angle = (double)ft_atoi(str);
    }
    return (1);
}