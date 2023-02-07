/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:20:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/11/29 14:52:49 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

float   rad_to_deg(float    x)
{
    float res;

    res = x * 180 / PI;
    return (res);
}

float deg_to_rad(float  x)
{
    float res;

    res = x * PI / 180;
    return (res);
}

float   normalize_ray(float rl, float ra, t_data    *data)
{
    float res;
    float rpa;

    if(ra < data->ply->pa)
        rpa = data->ply->pa - ra;
    else
        rpa = ra - data->ply->pa;
    res = rl * cos(deg_to_rad(rpa));

    return (res);
}