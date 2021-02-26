#include "xml.h"

int     free_pos(char **tab, int rus)
{
    int     i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (rus);
}

int     get_pos(char *str, t_pos *pos)
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
        return (free_pos(tab, 0));
    pos->x = ft_atoi(tab[0]);
    pos->y = ft_atoi(tab[1]);
    pos->z = ft_atoi(tab[2]);
    return (free_pos(tab, 1));
}