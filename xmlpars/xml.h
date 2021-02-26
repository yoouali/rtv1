#ifndef XML_H
# define XML_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

typedef struct  s_cam
{
    int     tab[4];
    double  origin[3];
    double  lookat[3];
    double  up[3];
    int     fov;
}               t_cam;

typedef struct  s_lgt
{
    int             tab[3];
    double          position[3];
    int             color;
    int             intensity;
    struct s_lgt    *next;
}               t_lgt;

typedef struct  s_obj
{
    int             type;
    int             tab[9];
    double          position[3];
    double          origin[3];
    double          rotation[3];
    double          radius;
    double          angle;
    int             color;
    int             diffuse;
    int             ambient;
    int             specular;
    struct s_obj   *next;
}               t_obj;

typedef struct  s_scene
{
    t_cam   *camera;
    t_lgt   *light;
    t_obj   *object;
}               t_scene;

typedef struct s_xml
{
    char    *line;
    int     ind;
    int     l;
    int     fd;
    t_scene *scene;
    void    *addr;
}              t_xml;

typedef struct     s_pos
{
    int     x;
    int     y;
    int     z;
}                   t_pos;

t_scene    *xml_parr(char *file);
int         check_file(t_xml *xml, int parent);
int         get_line(t_xml *xml, char *rule);
int         get_rule_number(char *rule);
int         get_rule(t_xml *xml, int parent, int *rule_num, char **rule);
int         check_rule_pose(int rule, int parent);
int         get_rule_end(t_xml *xml, char **rule);
void        *load_rule(t_xml *xml, int rule_num);
void        *load_obj(t_xml *xml, int rule_num);
void        *load_lgt(t_xml *xml);
int         read_data(t_xml *xml, int parent, int rule_num);
char        *get_string_data(t_xml *xml);
int         get_light_data(t_xml *xml, int rule_num, char *str);
int         get_camear_data(t_xml *xml, int rule_num, char *str);
int         get_pos(char *str, t_pos *pos);
int         free_pos(char **tab, int rus);
int         get_color(char *str);
int		    ft_indexof(char *s, char c);
int		    ft_pow(int nb, int exp);
int	        ft_contains(const char *set, char c);
int         get_object_data(t_xml *xml, int rule_num, char *str);
int         free_parr(char *rule, int rus);
t_scene     *leak_parr(t_xml *xml);
void        free_object(t_obj *obj);
void        free_light(t_lgt *lgt);
int         last_check(t_xml *xml);
int         check_object(t_obj *obj);
int         check_light(t_lgt *lgt);
void    set_object(t_obj *obj, int rule_num);

#endif