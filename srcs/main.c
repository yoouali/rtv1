/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/04 11:26:58 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double map(int position, int max_wh, double new_min_scope, double new_max_scope)
{
    double range;

    range = new_max_scope - new_min_scope;
    return (new_min_scope + position * (range / max_wh));
}

int main(int ac, char **av)
{
    t_rtv1 *rtv;
    t_scene *scene;

    ac = 0;
    scene = NULL;
    rtv = malloc(sizeof(t_rtv1));
    rtv->still_running = sdl_init_win(rtv);
    rtv->data = malloc(sizeof(int) * (WIDTH * HEIGHT));
    if (!(scene = xml_parsser(av[1])))
        return (0);
    t_scene *tmp;
    tmp = scene;
    while (rtv->still_running == 0)
    {
        if (SDL_PollEvent(&rtv->sdl.event))
        {
            ft_cast_rays(rtv, scene);
            SDL_UpdateTexture(rtv->sdl.texture, NULL, rtv->data, HEIGHT * sizeof(int));
            SDL_RenderCopy(rtv->sdl.renderer, rtv->sdl.texture, NULL, NULL);
            process_input(rtv);
            SDL_RenderPresent(rtv->sdl.renderer);
        }
    }
    return (0);
}
