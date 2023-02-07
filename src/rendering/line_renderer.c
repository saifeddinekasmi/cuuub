/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:11:57 by aelyakou          #+#    #+#             */
/*   Updated: 2022/11/30 00:52:21 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

inline int abs(int n) { return ((n > 0) ? n : -n ); }
 
void render_ray(int X0, int Y0, int X1, int Y1, t_data *data, int color)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        pixel_put_img(data->wrld, round(X), round(Y), color); 
        X += Xinc;
        Y += Yinc; 
    }
}