/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:56:09 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/03 21:37:11 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"


void    ft_init_data(t_data **data, t_map *map)
{

    (*data) = malloc(sizeof(t_data));
    (*data)->lvl = malloc(sizeof(t_map));
    (*data)->lvl = map;
    (*data)->mlx = malloc(sizeof(t_mlx));
    (*data)->ply = malloc(sizeof(t_ply));
    (*data)->wrld = malloc(sizeof(t_img));
    (*data)->north = malloc(sizeof(t_texture));
    (*data)->south = malloc(sizeof(t_texture));
    (*data)->east = malloc(sizeof(t_texture));
    (*data)->west = malloc(sizeof(t_texture));
}