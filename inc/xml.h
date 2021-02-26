# ifndef XML_H
#define XML_H

#include "rtv1.h"

typedef struct s_xmlpar
{
    int     fd;
    int     ind;
    void    *addr;
    char    *line;
    t_scene *scene;
}              t_xmlpar;


t_scene  *xml_parsser(char *file);
int         parrs_rule_end(t_xmlpar *xmlpar, char **rule);
int         parrs_rule(t_xmlpar *xmlpar, char **rule, int *rule_num, int parent);
int     check_light_structer(t_light *light);
int     check_object_structer(t_object *object);
int     structer_check(t_xmlpar xmlpar);
void    free_structer_light(t_light *light);
void    free_structer_object(t_object *object);
t_scene      *free_structer(t_scene *scene);
char    *get_string_data(t_xmlpar *xmlpar);
int     get_camera_data(t_xmlpar *xmlpar, int rule_num, char *str);
int     read_data(t_xmlpar *xmlpar, int rule_num, int parent);
void    set_object(t_object *object, int rule_num);
int     get_object_data(t_xmlpar *xmlpar, int rule_num, char *str);
int     get_light_data(t_xmlpar *xmlpar, int rule_num, char *str);
int     get_pos(char *str, t_vec3 *vec3);
int     free_pos(char **tab, char *str, int rus);
int     get_color_data(char *str);
int     get_rule(t_xmlpar *xmlpar, char **rule, int *rule_num, int parent);
int     check_rule_pos(int rule, int parent);
int     get_rule_num(char *rule);
void    *load_rule(t_scene *scene, int rule_num);
void    *load_object(t_scene *scene, int rule_num);
void    *load_light(t_scene *scene);
int     check_file(t_xmlpar *xmlpar, int parent);
int     free_parrser(char *rule, int ret);
int     get_line(t_xmlpar *xmlpar, char *rule, int *rule_num);

#endif