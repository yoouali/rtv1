#include "../../inc/xml.h"

int     get_rule_num(char *rule)
{
    if (!ft_strcmp(rule, "scene"))
        return (1);
    if (!ft_strcmp(rule, "camera"))
        return (2);
    if (!ft_strcmp(rule, "light"))
        return (3);
    if (!ft_strcmp(rule, "plane"))
        return (4);
    if (!ft_strcmp(rule, "sphere"))
        return (5);
    if (!ft_strcmp(rule, "cylinder"))
        return (6);
    if (!ft_strcmp(rule, "cone"))
        return (7);
    if (!ft_strcmp(rule, "origin"))
        return (8);
    if (!ft_strcmp(rule, "lookat"))
        return (9);
    if (!ft_strcmp(rule, "position"))
        return (10);
    if (!ft_strcmp(rule, "color"))
        return (11);
    if (!ft_strcmp(rule, "intensity"))
        return (12);
    if (!ft_strcmp(rule, "orientation"))
        return (13);
    if (!ft_strcmp(rule, "angle"))
        return (14);
    if (!ft_strcmp(rule, "radius"))
        return (15);
    if (!ft_strcmp(rule, "rotation"))
        return (16);
    if (!ft_strcmp(rule, "translation"))
        return (17);
    if (!ft_strcmp(rule, "fov"))
        return (18);
    return (0);
}

int     check_rule_pos(int rule, int parent)
{
    if (rule == 1 && parent != 0)
        return (0);
    if (parent == 1 && (rule < 2 || rule > 7))
        return (0);
    if (parent == 2 && rule != 8 && rule != 9 && rule != 18)
        return (0);
    if (parent == 3 && rule != 10 && rule != 12 && rule != 11)
        return (0);
    if (parent == 4 && rule != 11 && rule != 10 && rule != 13 && rule != 16 && rule != 17)
        return (0);
    if (parent == 5 && rule != 11 && rule != 10 && rule != 15 && rule != 16 && rule != 17)
        return (0);
    if (parent == 6 && rule != 10 && rule != 11 && rule != 13 && rule != 15 && rule != 16 && rule != 17)
        return (0);
    if (parent == 7 && rule != 11 && rule != 10 && rule != 13 && rule != 14 && rule != 16 && rule != 17)
        return (0);
    return (1);
}

int     get_rule(t_xmlpar *xmlpar, char **rule, int *rule_num, int parent)
{
    int     len;

    printf("iam in gget rule\n");
    len = 0;
    while (xmlpar->line[xmlpar->ind + len + 1] && xmlpar->line[xmlpar->ind + len +1] != '>')
        len++;
    if (xmlpar->line[xmlpar->ind + len + 1] == '\0')
        return (0);
    if (!(*rule = ft_strsub(xmlpar->line, xmlpar->ind + 1, len)))
        return (0);
    printf("the rule:%s \n", *rule);
    if (!(*rule_num = get_rule_num(*rule)))
        return (0);
    if (!(check_rule_pos(*rule_num, parent)))
        return (0);
    if (*rule_num > 1 && *rule_num < 8)
        if (!(xmlpar->addr = load_rule(xmlpar->scene, *rule_num)))
            return (0);
    xmlpar->ind = xmlpar->ind + 2 + len;
    printf("iam out from get rule\n");
    return (1);
}