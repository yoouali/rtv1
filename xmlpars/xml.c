#include "xml.h"

int         free_parr(char *rule, int rus)
{
    free(rule);
    return (rus);
}

int         get_line(t_xml *xml, char *rule)
{
    free(xml->line);
    xml->line = NULL;
    if ((get_next_line(xml->fd, &xml->line) < 1))
    {
        if (rule)
            return (free_parr(rule, -1));
        return (free_parr(rule, 1));
    }
    xml->l = xml->l + 1;
    xml->ind = 0;
    return (0);
}

int         check_file(t_xml *xml, int parent)
{
    int     rule_num;
    char    *rule;

    rule = NULL;
    while (1)
    {
        if (!xml->line || !xml->line[xml->ind])
        {
            if (get_line(xml, rule) != 0)
                return (0);
        }
        while (xml->line[xml->ind] == ' ' || xml->line[xml->ind] == '\t')
            xml->ind = xml->ind + 1;
        if (xml->line[xml->ind] && xml->line[xml->ind] != '<')
            return (free_parr(rule, -1));
        if (xml->line[xml->ind] == '<' && xml->line[xml->ind + 1] != '/')
        {
            if (!rule)
            {
                if(!get_rule(xml, parent, &rule_num, &rule))
                    return (free_parr(rule, -1));
            }
            else
            {
                if ((check_file(xml, rule_num)) == -1)
                    return (free_parr(rule, -1));
            }
            if (rule_num > 7)
                if (!read_data(xml, parent, rule_num))
                    return (free_parr(rule, -1));
        }
        if (xml->line[xml->ind] == '<' && xml->line[xml->ind + 1] == '/')
        {
            if (!get_rule_end(xml, &rule))
                return(free_parr(rule, -1));
            else
                return (free_parr(rule, 1));
        }
    }
}

t_scene    *xml_parr(char *file)
{
    t_xml   xml;

    xml.line = NULL;
    xml.ind = 0;
    xml.l = 0;
    xml.scene = NULL;

    xml.fd = open(file, O_RDONLY);
    if (!(xml.scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    xml.scene->camera = NULL;
    xml.scene->light = NULL;
    xml.scene->object = NULL;
    if ((check_file(&xml, 0) == -1) || (!last_check(&xml)))
        return (leak_parr(&xml));
    return (xml.scene);
}