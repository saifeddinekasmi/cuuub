/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_adds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:47:49 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/08 01:12:55 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	pixel_put_img(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if ((x >= 0 && x < (P_W * SSCL)) && (y >= 0 && y < P_H * SSCL))
	{
		dst = img->addr + (y * img->len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
