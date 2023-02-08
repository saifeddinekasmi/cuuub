/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:21:55 by skasmi            #+#    #+#             */
/*   Updated: 2023/02/08 01:22:26 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	render_slice(t_data *data, int slice, int x)
{
	int	y;

	if (slice > data->mlx->w_h)
		slice = data->mlx->w_h;
	y = (data->mlx->w_h / 2) - (slice / 2);
	while (y <= (data->mlx->w_h / 2) + (slice / 2))
	{
		pixel_put_img(data->wrld, x, y, 0x000000);
		y++;
	}
}

void	render_walls3d(t_data *data)
{
	int	slice;
	int	i;

	i = 0;
	while (i <= data->mlx->w_w - 1)
	{
		slice = UNIT / data->rays[i].dist * data->dsp;
		render_slice(data, slice, i);
		i++;
	}
}

int	keyup(int keycode, t_data *data)
{
	if (keycode == 123 || keycode == 124)
		data->ply->r_dir = 0;
	if (keycode == 13 || keycode == 1)
		data->ply->mv_dir = 0;
	if (keycode == 0 || keycode == 2)
	{
		data->ply->d_dir = 0;
		data->ply->mh_dir = 0;
	}
	return (0);
}

void	get_m_dir(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->ply->mv_dir = 1;
		return ;
	}
	if (keycode == 1)
	{
		data->ply->mv_dir = -1;
		return ;
	}
	if (keycode == 0)
	{
		data->ply->mh_dir = 1;
		data->ply->d_dir = -1;
	}
	if (keycode == 2)
	{
		data->ply->mh_dir = 1;
		data->ply->d_dir = 1;
	}
}

void	get_r_dir(int keycode, t_data *data)
{
	if (keycode == 124)
	{
		data->ply->r_dir = -1;
		return ;
	}
	if (keycode == 123)
	{
		data->ply->r_dir = 1;
		return ;
	}
}
