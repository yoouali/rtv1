#include "xml.h"

int         get_rule_number(char *rule)
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
    if (!ft_strcmp(rule, "rotation"))
        return (13);
    if (!ft_strcmp(rule, "angle"))
        return (14);
    if (!ft_strcmp(rule, "radius"))
        return (15);
    if (!ft_strcmp(rule, "diffuse"))
        return (16);
    if (!ft_strcmp(rule, "ambient"))
        return (17);
    if (!ft_strcmp(rule, "specular"))
        return (18);
    if (!ft_strcmp(rule, "fov"))
        return (19);
    if (!ft_strcmp(rule, "up"))
        return (20);
    return (-1);
}

int         get_rule(t_xml *xml, int parent, int *rule_num, char **rule)
{
    int     len;

   len = 0;
    while (xml->line[xml->ind+1+len] && xml->line[xml->ind+1+len] != '>')
        len++;
    if (xml->line[xml->ind+1+len] == '\0')
        return (0);
    if (!(*rule = ft_strsub(xml->line, xml->ind+1, len)))
        return (0);
    xml->ind = xml->ind + len + 2;
    if ((*rule_num = get_rule_number(*rule)) == -1)
        return (0);
    if (!check_rule_pose(*rule_num, parent))
        return (0);
    if (*rule_num > 1 && *rule_num < 8)
    {
        if (!(xml->addr = load_rule(xml, *rule_num)))
            return (0);
    }
    printf("the rule : %s\n", *rule);
    return (1);
}

int         check_rule_pose(int rule, int parent)
{
    if (rule == 1 && parent != 0)
        return (0);
    if (parent == 1 && (rule < 2 || rule > 7))
        return (0);
    if (parent == 2 && rule != 8 && rule != 9 && rule != 19 && rule != 20)
        return (0);
    if (parent == 3 && rule != 10 && rule != 12 && rule != 11)
        return (0);
    if (parent == 4 && rule != 11 && rule != 10 && rule != 13 && rule != 16 && rule != 17 && rule != 18)
        return (0);
    if (parent == 5 && rule != 11 && rule != 8 && rule != 15 && rule != 16 && rule != 17 && rule != 18)
        return (0);
    if (parent == 6 && rule != 8 && rule != 11 && rule != 13 && rule != 15 && rule != 16 && rule != 17 && rule != 18)
        return (0);
    if (parent == 7 && rule != 11 && rule != 8 && rule != 13 && rule != 14 && rule != 16 && rule != 17 && rule != 18)
        return (0);
    return (1);
}

int         get_rule_end(t_xml *xml, char **rule)
{
    int     len;
    char    *end;
    int     rus;

   len = 0;
   end = NULL;
   rus = 1;
    while (xml->line[xml->ind+2+len] && xml->line[xml->ind+2+len] != '>')
        len++;
    if (xml->line[xml->ind+2+len] == '\0')
        rus = 0;
    if (!(end = ft_strsub(xml->line, xml->ind+2, len)))
        rus = 0;
    if (ft_strcmp(*rule, end))
        rus = 0;
    xml->ind = xml->ind + len + 3;
    printf("the rule end:  %s\n", end);
    free(end);
    free(*rule);
    *rule = NULL;
    return (rus);
}