#include "../../inc/xml.h"

int     free_pos(char **tab, char *str, int rus)
{
    int     i;

    i = 0;
    while (tab[i])
    {
        free (tab[i]);
        i++;
    }
    free (tab);
    free (str);
    return (rus);
}

int     get_pos(char *str, t_vec3 *vec3)
{
    char    **tab;
    int     len;

    tab = NULL;
    if (!(tab = ft_strsplit(str, ',')))
        return (0);
    len = 0;
    while (tab[len])
        len++;
    if (len != 3)
        return (free_pos(tab, str, 0));
    vec3->x = (double)ft_atoi(tab[0]);
    vec3->y = (double)ft_atoi(tab[1]);
    vec3->z = (double)ft_atoi(tab[2]);
    return (free_pos(tab, str, 1));
}

int     get_light_data(t_xmlpar *xmlpar, int rule_num, char *str)
{
    t_vec3  vec3;
    t_light *light;
    int     color;
    
    light = (t_light *)xmlpar->addr;
    if (rule_num == 12 && light->tab[2] == 0)
        {
            light->tab[2] = 1;
            light->intensity = (double)ft_atoi(str);
            return (1);
        }
    if (rule_num == 11 && light->tab[1] == 0)
    {
        color = get_color_data(str);
        light->tab[1] = 1;
        light->color.x = (color >> 16) & 255;
        light->color.y = (color >> 8) & 255;
        light->color.z = color & 255;
        return (1);
    }
    if (rule_num == 10 && light->tab[0] == 0)
    {
        if (!get_pos(str, &vec3))
            return (0);
        light->tab[0] = 1;
        light->pos.x = vec3.x;
        light->pos.y = vec3.y;
        light->pos.z = vec3.z;
        return (1);
    }
    return (0);
}