/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:41:56 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/08 01:21:46 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"





int	update(t_data	*data)
{
	p_move(data);
	p_rotate(data);
	mlx_clear_window(data->mlx->mp, data->mlx->w3);
	mlx_destroy_image(data->mlx->mp, data->wrld->img);
	data->wrld->img = mlx_new_image(data->mlx->mp,data->mlx->w_w, data->mlx->w_h);
	render_sky(data, 0x66b3d1, data->wrld);
	render_floor(data, 0x3d874a, data->wrld);
	loop_rays(data);
	render_walls3d(data);
	// render_level2d(data);
	mlx_put_image_to_window(data->mlx->mp, data->mlx->w3, data->wrld->img, 0, 0);
	return (0);
}

int ft_find_char(char	c)
{
	if(c == 'N')
		return (90);
	if(c == 'S')
		return (270);
	if(c == 'E')
		return (0);
	if(c == 'W')
		return (180);
	return (1);
}

void ft_return_map_square(t_map *map)
{
	int i;
	int j;

	i = 0;
	map->p_orient = 1;
	while (map->only_map[i])
	{
		j = 0;
		while (map->only_map[i][j])
		{
			if(map->p_orient == 1)
				map->p_orient = ft_find_char(map->only_map[i][j]);
			if (map->only_map[i][j] == ' ')
				map->only_map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	keydown(int keycode, t_data	*data)
{
	get_m_dir(keycode, data);
	get_r_dir(keycode, data);
	if (keycode == 53)
		ft_quit(data);
	return (keycode);
}

int main(int ac, char **av)
{
	t_data	*data;
	t_map		map;
	t_texture	t;

//*********
	t.ea = NULL;
	t.no = NULL;
	t.so = NULL;
	t.we = NULL;
	map.t = &t;
	map.line_empty = 0;
	if (ac != 2)
	{
		printf("Error Args !!!\n");
		exit(1);
	}
	if (ft_check_file_map(av) == 1)
	{
		printf("\033[0;31mextention of map must finished -> .cub !!\n");
		exit(1);
	}
	ft_read_map(&map, av);
	map.map_width = get_len(map.all_map2d);
	ft_check_line_before_map(map.all_map2d, &map);
	ft_check_map_len(&map);
	if (ft_export_only_map2d(&map) == 1)
	{
		printf("errooooor");
		exit(1);
	}
	map.width_only_map = get_width(map.only_map);
	map.height_only_map = get_height(map.only_map);
	retrun_map_2d_withspace(&map);
	if (ft_check_content(&map) || ft_check_all_map(map.only_map) ||
		ft_check_horizontal(&map) || ft_check_vertical(&map))
	{
		printf("error walls content\n");
		exit(EXIT_FAILURE);
	}
	ft_return_map_square(&map);
	data = get_data(&map);
	if (!data)
		return (0);
/*******/
	data->lvl->cl_c = create_rgb(data->lvl->r_c, data->lvl->g_c, data->lvl->b_c);
	data->lvl->fl_c = create_rgb(data->lvl->r_f, data->lvl->g_f, data->lvl->b_f);
	mlx_hook(data->mlx->w3, 2, 0, keydown, data);
	mlx_hook(data->mlx->w3, 3, 0, keyup, data);
	mlx_hook(data->mlx->w3, 17,0, ft_quit, data);
	mlx_loop_hook(data->mlx->mp, update, data);
	mlx_loop(data->mlx->mp);
	return(0);
}