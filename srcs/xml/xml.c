#include "../../inc/xml.h"

int         parrs_rule(t_xmlpar *xmlpar, char **rule, int *rule_num, int parent)
{
    if (!*rule)
    {
        if (!get_rule(xmlpar, rule, rule_num, parent))
            return (0);
    }
    else
    {
        if (check_file(xmlpar, *rule_num) == -1)
            return (0);
    }
    if (*rule_num > 7)
    {
        if (!read_data(xmlpar, *rule_num, parent))
            return (0);
    }
    return (1);
}

int         parrs_rule_end(t_xmlpar *xmlpar, char **rule)
{
    int     len;
    char    *end;
    int     rus;

    len = 0;
    end = NULL;
    rus = 1;
    while (xmlpar->line[xmlpar->ind + 2 + len] && xmlpar->line[xmlpar->ind + 2 + len] != '>')
        len++;
    if (!xmlpar->line[xmlpar->ind + 2 + len])
        rus = 0;
    if (!(end = ft_strsub(xmlpar->line, xmlpar->ind + 2, len)))
        rus = 0;
    if (ft_strcmp(*rule, end))
        rus = 0;
    xmlpar->ind = xmlpar->ind + 3 + len;
    free(end);
    return (rus);
}

t_scene  *xml_parsser(char *file)
{
    t_xmlpar    xmlpar;

    xmlpar.ind = 0;
    xmlpar.addr = NULL;
    xmlpar.line = NULL;
    if (!(xmlpar.scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    xmlpar.scene->camera =  NULL;
    xmlpar.scene->light = NULL;
    xmlpar.scene->object = NULL;
    xmlpar.scene->camera = NULL;
    xmlpar.scene->light = NULL;
    xmlpar.scene->object = NULL;
    xmlpar.fd = open(file, O_RDONLY);
    if (check_file(&xmlpar, 0) == -1 || !structer_check(xmlpar))
        return (free_structer(xmlpar.scene));
    return (xmlpar.scene);
}