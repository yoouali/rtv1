/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:15:55 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/24 15:39:36 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
#include "rtv1.h"

/*
    SDL
*/

int			sdl_init_texture(t_rtv1	*rtv);
int         sdl_init_render(t_rtv1   *rtv);
int			sdl_init_win(t_rtv1	*rtv);

#endif