#include "../../inc/xml.h"

int     get_line(t_xmlpar *xmlpar, char *rule, int *rule_num)
{
    printf("iam in get lien\n");
    free(xmlpar->line);
    xmlpar->line = NULL;
    if (get_next_line(xmlpar->fd, &xmlpar->line) < 1)
    {
        if (rule)
            *rule_num = -1;
        else
            *rule_num = 0;
        return (0);
    }
    xmlpar->ind = 0;
    printf("dazt line\n");
    return (1);
}

int     free_parrser(char *rule, int ret)
{
    free(rule);
    printf("id this a problem\n");
    return (ret);
}

int     check_file(t_xmlpar *xmlpar, int parent)
{
    int     rule_num;
    char    *rule;

    rule = NULL;
    while (1)
    {
        printf("loop beg\n");
        if (!xmlpar->line || !xmlpar->line[xmlpar->ind])
            if (get_line(xmlpar, rule, &rule_num) == 0)
                return (free_parrser(rule, rule_num));
        printf("after get line\n");
        while (xmlpar->line[xmlpar->ind] == '\t' || xmlpar->line[xmlpar->ind] == ' ')
            xmlpar->ind = xmlpar->ind + 1;
        if (xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] != '<')
            return (free_parrser(rule, -1));
        printf("after space loop\n");
        if(xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] == '<' && xmlpar->line[xmlpar->ind + 1] != '/')
            if (parrs_rule(xmlpar, &rule, &rule_num, parent) == 0)
                return (free_parrser(rule, -1));
        printf("after get rule\n");
        printf("the index of line %d\n", xmlpar->ind);
        if (xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] == '<' && xmlpar->line[xmlpar->ind + 1] == '/')
        {
            printf("before end rule | rule : %s\n", rule);
            return (free_parrser(rule, parrs_rule_end(xmlpar, &rule)));
        }
        printf("loop end\n");
    } 
    return (0);   
}