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