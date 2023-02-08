/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:18:18 by skasmi            #+#    #+#             */
/*   Updated: 2023/02/08 01:19:08 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_quit(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

void	loop_rays(t_data *data)
{
	int	i;

	data->rays = malloc(sizeof(t_ray) * data->mlx->w_w - 1);
	i = data->mlx->w_w - 1;
	while (i >= 0)
	{
		data->rays[i].dist = cast_ray(data, i);
		i--;
	}
}

void	render_sky(t_data *data, int color, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	(void)color;
	while (y < data->mlx->w_h / 2)
	{
		x = 0;
		while (x < data->mlx->w_w)
		{
			pixel_put_img(img, x, y, data->lvl->cl_c);
			x++;
		}
		y++;
	}
}

void	render_floor(t_data *data, int color, t_img *img)
{
	int	x;
	int	y;

	(void)color;
	y = data->mlx->w_h / 2;
	while (y < data->mlx->w_h)
	{
		x = 0;
		while (x < data->mlx->w_w)
		{
			pixel_put_img(img, x, y, data->lvl->fl_c);
			x++;
		}
		y++;
	}
}

void	is_collided(float x, float y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / UNIT;
	map_y = y / UNIT;
	if (data->lvl->only_map[map_y][map_x]
		&& data->lvl->only_map[map_y][map_x] == '1')
		return ;
	else
	{
		data->ply->p_pos->x = x;
		data->ply->p_pos->y = y;
	}
	return ;
}
