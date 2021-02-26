/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:58:02 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/18 14:47:27 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

double    vec_length(t_vec3 vec)
{
    double length;

    length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    return (length);
}

t_vec3    plus(t_vec3 a, t_vec3 b)
{
    t_vec3    res;

    res.x=(a.x + b.x);
    res.y=(a.y + b.y);
    res.z=(a.z + b.z);
    return (res);
}

t_vec3    minus(t_vec3 a, t_vec3 b)
{
    t_vec3    res;

    res.x=(a.x - b.x);
    res.y=(a.y - b.y);
    res.z=(a.z - b.z);
    return (res);
}

t_vec3    mult2(double t, t_vec3 b)
{
    t_vec3    res;

    res.x=(t * b.x);
    res.y=(t * b.y);
    res.z=(t * b.z);
    return (res);
}

t_vec3    mult(t_vec3 a, t_vec3 b)
{
    t_vec3    res;

    res.x=(a.x * b.x);
    res.y=(a.y * b.y);
    res.z=(a.z * b.z);
    return (res);
}

t_vec3    divide(t_vec3 b, double t)
{
    return (mult2((1/t), b));
}

double    dot(t_vec3    a, t_vec3 b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3    cross(t_vec3 a, t_vec3 b)
{
    t_vec3    res;
    

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return (res);
}

t_vec3    normalize(t_vec3 vec)
{
    return (divide(vec, vec_length(vec)));
}