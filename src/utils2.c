/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:20:52 by skasmi            #+#    #+#             */
/*   Updated: 2023/02/08 01:21:28 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	diag_move(t_data *data)
{
	float	new_x;
	float	new_y;
	float	rad;

	if (data->ply->d_dir == 1)
		rad = deg_to_rad(limit_angles(data->ply->pa - 90));
	if (data->ply->d_dir == -1)
		rad = deg_to_rad(limit_angles(data->ply->pa + 90));
	new_x = data->ply->p_pos->x + cosf(rad) * MVS * data->ply->mh_dir;
	new_y = data->ply->p_pos->y - sinf(rad) * MVS * data->ply->mh_dir;
	is_collided(new_x, new_y, data);
}

void	p_move(t_data *data)
{
	float	rad;
	float	new_y;
	float	new_x;

	if (data->ply->d_dir != 0)
	{
		diag_move(data);
		return ;
	}
	rad = deg_to_rad(data->ply->pa);
	new_x = data->ply->p_pos->x + cosf(rad) * MVS * data->ply->mv_dir;
	new_y = data->ply->p_pos->y - sinf(rad) * MVS * data->ply->mv_dir;
	is_collided(new_x, new_y, data);
}

void	p_rotate(t_data *data)
{
	data->ply->pa += TRS * data->ply->r_dir;
	data->ply->pa = limit_angles(data->ply->pa);
}

void	render_wall2d(int x, int y, t_data *data)
{
	int	i;
	int	j;
	int	n_unit;
	int	ox;

	i = 0;
	n_unit = (UNIT)-1;
	ox = x;
	while (i <= n_unit)
	{
		ox = x;
		j = 0;
		while (j <= n_unit)
		{
			pixel_put_img(data->wrld, ox / 4, y / 4, 0xfc6f03);
			j++;
			ox++;
		}
		y++;
		i++;
	}
}

void	render_level2d(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->lvl->only_map[i])
	{
		j = 0;
		while (data->lvl->only_map[i][j])
		{
			if (data->lvl->only_map[i][j] == '1')
				render_wall2d(j * UNIT, i * UNIT, data);
			j++;
		}
		i++;
	}
}
