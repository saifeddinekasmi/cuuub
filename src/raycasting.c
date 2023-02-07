/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:21:10 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/04 15:29:46 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int get_dir_v(float   ra)
{
    int res;

    res = 0;
    if(ra == 0)
        return (res);
    if (ra > 180)
        res = 1;
    else if (ra < 180)
        res = -1;
    return (res);
}

int get_dir_h(float ra)
{
    int res;
    
    res = 0;
    if(ra == 90 || ra == 270)
        return (res);
    if(ra > 90 && ra < 270)
        return (res = -1, res);
    if(ra < 90 || ra > 270)
        res = 1;
    return (res);
}

float   get_hwy(t_data  *data, int dir)
{
    int wy;
    
    if(dir == -1)
    {
        wy = (floor(data->ply->p_pos->y / UNIT) * UNIT);
    }
    if(dir == 1)
    {
        wy = (floor(data->ply->p_pos->y / UNIT) * UNIT) + UNIT;
    }
    return (wy);
}

float   get_vwx(t_data  *data, int dir)
{
    float wx;
    
    if(dir == -1)
    {
        wx = ((int)(data->ply->p_pos->x / UNIT) * UNIT);
    }
    if(dir == 1)
    {
        wx = ((int)(data->ply->p_pos->x / UNIT) * UNIT) + UNIT;
    }
    return (wx);
}

t_pos   check_wall_h(double  *res, float ra, t_data   *data)
{
    double   xa;
    double   ya;
    int     dir;
    t_pos   wpos;

    wpos.x = 0;
    wpos.y = 0;
    *res = 0;
    dir = get_dir_v(ra);
    if(dir == 0)
        return (*res = INFINITY, wpos);
    ya = UNIT * dir;
    xa = ya / -tanf(deg_to_rad(ra));
    wpos.y = get_hwy(data, dir);
    wpos.x = data->ply->p_pos->x + ((data->ply->p_pos->y - wpos.y) / tanf(deg_to_rad(ra)));
    if((int)(wpos.x/UNIT) >= data->lvl->width_only_map || (int)(wpos.x/UNIT) <= 0)
        return (*res = INFINITY, wpos);
    if(dir == -1)
        wpos.y -= 1; 
    while(data->lvl->only_map[(int)(wpos.y/UNIT)][(int)(wpos.x/UNIT)] != '1')
    {
        wpos.x += xa;
        wpos.y += ya;
        if((int)(wpos.x/UNIT) >= data->lvl->width_only_map || (int)(wpos.x/UNIT) <= 0)
            break;
    }
    *res = sqrtf(powf((data->ply->p_pos->x - wpos.x), 2) + powf((data->ply->p_pos->y - wpos.y), 2));
    return (wpos);
}

t_pos   check_wall_v(double  *res, float ra, t_data   *data)
{
    double xa;
    double ya;
    int   dir;
    t_pos wpos;

    wpos.x = 0;
    wpos.y = 0;
    *res = 0;
    dir = get_dir_h(ra);
    if(dir == 0)
        return (*res = INFINITY, wpos);
    xa = UNIT * dir;
    ya = xa * -tanf(deg_to_rad(ra));
    wpos.x = get_vwx(data, dir);
    wpos.y =  data->ply->p_pos->y + ((data->ply->p_pos->x - wpos.x) * tanf(deg_to_rad(ra)));
    if(dir == -1)
        wpos.x -= 1; 
    if((int)(wpos.y/UNIT) >= data->lvl->height_only_map || (int)(wpos.y/UNIT) <= 0)
        return (*res = INFINITY, wpos);
    while(data->lvl->only_map[(int)floor(wpos.y/UNIT)][(int)floor(wpos.x/UNIT)] != '1')
    {
        wpos.x += xa;
        wpos.y += ya;
        if((int)(wpos.y/UNIT) >= data->lvl->height_only_map || (int)(wpos.y/UNIT) <= 0)
            return (*res = INFINITY, wpos);
    }
    *res = sqrtf(powf((data->ply->p_pos->x - wpos.x), 2) + powf((data->ply->p_pos->y - wpos.y), 2));
    return (wpos);
}

float    cast_ray(t_data    *data, int  i)
{
    double   h;
    double   v;
    float   ra;
    t_pos   wposv;
    t_pos   wposh;

    ra = (data->ply->pa + 30.0) - ((float)(i) * data->abr);
    ra = limit_angles(ra);
    h = INFINITY;
    v = INFINITY;
    wposv = check_wall_v(&v, ra, data);
    wposh = check_wall_h(&h, ra, data);
    if(h >= v)
    {
        data->rays[i].is_v = 1;
        data->rays[i].wall_pos = wposv;
        return (normalize_ray(v, ra, data));
    }
    if(h < v)
    {
        data->rays[i].wall_pos = wposh;
        return (normalize_ray(h, ra, data));
    }
    return (INFINITY);
}