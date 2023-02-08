/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:20:35 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/08 01:15:54 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

float	rad_to_deg(float x)
{
	float	res;

	res = x * 180 / PI;
	return (res);
}

float	deg_to_rad(float x)
{
	float	res;

	res = x * PI / 180;
	return (res);
}

float	normalize_ray(float rl, float ra, t_data *data)
{
	float	res;
	float	rpa;

	if (ra < data->ply->pa)
		rpa = data->ply->pa - ra;
	else
		rpa = ra - data->ply->pa;
	res = rl * cos(deg_to_rad(rpa));
	return (res);
}
