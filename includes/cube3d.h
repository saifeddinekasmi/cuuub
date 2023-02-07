/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:41:59 by aelyakou          #+#    #+#             */
/*   Updated: 2023/02/06 20:52:28 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H
#include <stdio.h>
#include "mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include <stdbool.h>
#include "../Parssing/cub3d.h"



#define STDERR 2 
#define NO 1
#define SO 2
#define WE 3
#define EA 4
//here im defining constants that we'll be using through the program ;; (((im gonna explain what the projection plane is when ur here its kinda abstract)));;;
#define UNIT	64			//HOW MANY PIXELS IN EACH GRID UNIT; (( grid unit is the size dimensions of the cubes we're drawing  ));;;
#define	P_W		200			//WIDTH OF THE PROJECTION PLANE;
#define	P_H		200	//HEIGHT OF THE PROJECTION PLANE;
#define PI		3.14159265358979323846		//APPROXIMATE VALUE OF PI
#define	MVS		5			//movement speed of player
#define	TRS		2			//turning speed of player
#define	SSCL	4			//screen scaler == (P_W * SSCL && P_H * SSCL)
#define	MSCL	8			//MINIMAP SCALER == (SCREEN WIDTH / MSCL && SCREEN HEIGHT / MSCL)

//this whole struct is created as an optimization process, to avoid using mlx_put_pixel, because its damn slow, so we'll create our own.
typedef struct s_mlx
{
	void    *mp; //mlx_pointer;
	void	*w3; //window_pointer to 3D rendering;
	int		w_h;
	int		w_w;
}               t_mlx;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endn;
	t_mlx	t;
}				t_img;



typedef	struct	s_pos
{
	float		x; // ta hadi khsni nshr7alk albegra dzb ???
	float		y;
}				t_pos;

//player struct;
typedef struct  s_ply
{
	t_pos		*p_pos; // player position;
	float		fov; // field of view;
	float		p_alt; // player altitude/height;
	float		pa;		//player angle;
	int			m_dir;
	int			r_dir;
}               t_ply;

//------------t_lvl var description for dummies hhhhhh-------------
/*
l_w == level_width;
l_h == level_height;
cco = ceiling color;
fco = floor color;
no = north texture pathname;
so = south texture pathname;
we = west texture pathname;
ea = east texture pathname;
btw fill map empty spaces with 0s;
*/

typedef struct s_ray
{
	float	dist;
	t_pos	wall_pos;
	int		is_v;
	char	intersected;
}				t_ray;

typedef struct s_textures
{
	void	*img;
	int		width;
	int		height;
	int		*buff;
	int		bpp;
	int		len;
}				t_textures;
//t_data is the struct we gonna assign all our other main structs into in main for ease of parameter passing; lghlid dzb;;
typedef struct	s_data
{
	t_ply		*ply;
	t_mlx		*mlx;
	float		abr; //angle between rays;
	float		dsp; //distance between player and projection plane;
	t_ray		*rays;
	t_img		*wrld;
	t_textures	*north;
	t_textures	*south;
	t_textures	*east;
	t_textures	*west;
	t_map		*lvl;

}				t_data;

//--------------level parsing functions----------------
void	ft_init_data(t_data **data, t_map *map);
char    **get_map();
t_data  *get_data(t_map *map);

//-----------free fucntions
void    free_tab(char **tab);

//--------------level drawing functions----------------

//--------------math funcs-------------------

float   limit_angles(float ra);
float   rad_to_deg(float  x);
float	deg_to_rad(float  x);
float   normalize_ray(float rl, float ra, t_data    *data);

//--------------raycasting funcs------------------------

float	cast_ray(t_data    *data, int i);
void	render_ray(int X0, int Y0, int X1, int Y1, t_data *data, int color);

//-------------mlx_mods---------------------------------

void	pixel_put_img(t_img *img, int x, int y, unsigned int color);


#endif