/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:15:04 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/08 01:16:56 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	p_pos_init(t_pos *pos, t_map *lvl)
{
	int	i;
	int	j;

	i = 0;
	while (lvl->only_map[i])
	{
		j = 0;
		while (lvl->only_map[i][j])
		{
			if (lvl->only_map[i][j] == 'S' || lvl->only_map[i][j] == 'E'
				|| lvl->only_map[i][j] == 'W' || lvl->only_map[i][j] == 'N')
			{
				pos->x = j * UNIT + (UNIT / 2);
				pos->y = i * UNIT + (UNIT / 2);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->w_h = P_H * SSCL;
	mlx->w_w = P_W * SSCL;
	mlx->mp = mlx_init();
	mlx->w3 = mlx_new_window(mlx->mp, mlx->w_w, mlx->w_h, "CUB3D");
}

void	plyr_init(t_ply *ply, t_map *lvl)
{
	ply->fov = 60;
	ply->p_alt = UNIT / 2;
	ply->pa = lvl->p_orient;
	ply->p_pos = malloc(sizeof(t_pos));
	ply->r_dir = 0;
	ply->mv_dir = 0;
	ply->mh_dir = 0;
	ply->d_dir = 0;
	p_pos_init(ply->p_pos, lvl);
}

void	img_init(t_data *data)
{
	data->wrld->img = mlx_new_image(data->mlx->mp, data->mlx->w_w,
			data->mlx->w_h);
	data->wrld->addr = mlx_get_data_addr(data->wrld->img, &data->wrld->bpp,
			&data->wrld->len, &data->wrld->endn);
}

t_data	*get_data(t_map *map)
{
	t_data	*data;

	ft_init_data(&data, map);
	init_mlx(data->mlx);
	plyr_init(data->ply, data->lvl);
	img_init(data);
	data->dsp = ((data->mlx->w_w / 2) / tanf(deg_to_rad(data->ply->fov / 2)));
	data->abr = data->ply->fov / data->mlx->w_w;
	return (data);
}
