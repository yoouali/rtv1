#include "xml.h"

int main(int ac, char **av)
{
    t_scene *scene;

    int i = 1;
    scene = NULL;
    if (ac == 2)
        scene = xml_parr(av[1]);
    if (scene)
    {
        printf("camera :\n");
        printf("origin : x:%d | y:%d | z:%d\n", (int)scene->camera->origin[0], (int)scene->camera->origin[1], (int)scene->camera->origin[2]);
        printf("lookat : x:%d | y:%d | z:%d\n", (int)scene->camera->lookat[0], (int)scene->camera->lookat[1], (int)scene->camera->lookat[2]);
        printf("up : x:%d | y:%d | z:%d\n", (int)scene->camera->up[0], (int)scene->camera->up[1], (int)scene->camera->up[2]);
        printf("fov : %d\n", scene->camera->fov);
        if (scene->light)
        {
            while (scene->light)
            {
                printf("position : x:%d | y:%d | z:%d\n", (int)scene->light->position[0], (int)scene->light->position[1], (int)scene->light->position[3]);
                printf("intensity : %d\n", scene->light->intensity);
                printf("color : %d\n", scene->light->color);
                scene->light = scene->light->next;
            }
        }
        if (scene->object)
        {
            while (scene->object)
            {
                if (scene->object->type > 0)
                    printf("origin : x:%d | y:%d | z:%d\n", (int)scene->object->origin[0], (int)scene->object->origin[1], (int)scene->object->origin[2]);
                if (scene->object->type == 0)
                    printf("position : x:%d | y:%d | z:%d\n", (int)scene->object->position[0], (int)scene->object->position[1], (int)scene->object->position[2]);
                if (scene->object->type != 1)
                    printf("rotation : x:%d | y:%d | z:%d\n", (int)scene->object->rotation[0], (int)scene->object->rotation[1], (int)scene->object->rotation[2]);
                if (scene->object->type == 1 || scene->object->type == 2)
                    printf("radius : %d\n", (int)scene->object->radius);
                if (scene->object->type == 3)
                    printf("angle : %d\n", (int)scene->object->angle);
                printf("color : %d\n", scene->object->color);
                printf("diffuse : %d\n", scene->object->diffuse);
                printf("ambient : %d\n", scene->object->ambient);
                printf("specular : %d\n", scene->object->specular);
                scene->object = scene->object->next;
            }
        }
    }
    return (0);
}