#include "../../inc/xml.h"

int         parrs_rule(t_xmlpar *xmlpar, char **rule, int *rule_num, int parent)
{
    printf("in parrs_rule \n");
    if (!*rule)
    {
        printf("call get rule\n");
        if (!get_rule(xmlpar, rule, rule_num, parent))
            return (0);
        printf("rule: %s\n", *rule);
    }
    else
    {
        printf("recurseve rule\n");
        if (check_file(xmlpar, *rule_num) == -1)
            return (0);
        printf("out of recurev rule\n");
    }
    if (*rule_num > 7)
    {
        printf("call get data\n");
        if (!read_data(xmlpar, *rule_num, parent))
            return (0);
        printf("get data over\n");
    }
    printf("out of parrs_rule \n");
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
    printf("rule end\n");
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
    printf("parsser beging\n");
    if (check_file(&xmlpar, 0) == -1 || !structer_check(xmlpar))
        return (free_structer(xmlpar.scene));
    printf("parsing end \n");
    return (xmlpar.scene);
}