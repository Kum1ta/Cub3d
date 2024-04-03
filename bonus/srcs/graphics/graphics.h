/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:53 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 15:15:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "cub3d.h"

# define WIDTH 1024
# define HEIGHT 768
# define TIME_PER_FRAME_US 0
# define PI 3.14159265

# define MIDSCREEN_POSX WIDTH / 2
# define MIDSCREEN_POSY HEIGHT / 2

typedef struct s_raydata
{
	float	imgXPercent;
	bool	found;
	t_block	*block;
	float	dist;
	int		dir;
	int		wall_start;
	int		wall_size;
	int		wall_end;
	int		diff;
}	t_raydata;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef enum e_menu
{
	MAIN_MENU,
	MAP_LARG_MENU,
	GAME,
	OPTIONS,
	NOTHING,
}	t_menu;

typedef enum e_inventory
{
	WEAPON_INV,
	KNIFE_INV,
	FIST_INV,
}	t_inventory;

typedef struct s_mouse
{
	int		x;
	int		y;
	int		last_x;
	int		last_y;
	bool	pressed_left;
	bool	pressed_right;
}	t_mouse;

typedef struct s_menu_map
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		size;
	int		initial_size;
}	t_menu_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_loadeds_textures
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
	t_img	*floor;
	t_img	*ceiling;
	t_img	*player_ico;
	t_img	*weapon_inv;
	t_img	*fist_inv;
	t_img	*knife_inv;
	t_img	*weapon_game;
	t_img	*fist_game;
	t_img	*knife_game;
	t_img	*fire_gun;
}	t_loadeds_textures;

typedef struct s_keyboard
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	r;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	esc;
	bool	e;
}	t_keyboard;

typedef struct s_player
{
	int					health;
	t_inventory			actual_weapon;
	int					ammo;
	int					xy_item[2];
	bool				is_reloading;
	struct s_raydata	front_ray;
}	t_player;

typedef struct s_mlx
{
	t_mouse				*mouse;
	t_map				*map;
	t_menu_map			*menu_map;
	t_loadeds_textures	*textures;
	t_player			*player;
	void				*mlx;
	void				*win;
	t_menu				actuel_menu;
	t_keyboard			*keyboard;
	void				*tmp;
}	t_mlx;

/* ############################ DEBUG FUNCTION ############################# */
void	info_player(t_mlx *mlx);

/* ------ main_graphics.c -------------------------------------------------- */
int		window(int event, void *mlx_ptr);

/* ------ update.c --------------------------------------------------------- */
int		update(void *mlx_ptr);

/* ------ init.c ----------------------------------------------------------- */
int		init(t_mlx *mlx, t_map *map);

/* ------ larg_map.c ------------------------------------------------------- */
void	larg_map(t_mlx *mlx, int need_free);

/* ------ load_textures.c -------------------------------------------------- */
int		load_textures(t_mlx *mlx);

/* ------ free_all.c ------------------------------------------------------- */
int		free_all_graphics(t_mlx *mlx);

/* ------ destroy_textures.c ----------------------------------------------- */
int		destroy_textures(t_mlx *mlx);

/* ------ keyboard.c ------------------------------------------------------- */
void	keyboard_status(int key_code[2], bool *key, bool from, bool to);
int		keyboard_down(int key, void *mlx_ptr);
int		keyboard_up(int key, void *mlx_ptr);
int		keyboard(t_mlx *mlx);

/* ------ gane_keyboard.c -------------------------------------------------- */
void	game_keyboard(t_mlx *mlx);

/* ------ map_larg_menu_keyboard.c ----------------------------------------- */
void	larg_map_keyboard(t_mlx *mlx);

/* ------ mouse_wheel.c ---------------------------------------------------- */
int		mouse_whell(int button, void *mlx_ptr);

/* ------ mouse_down.c ----------------------------------------------------- */
int		mouse_down(int button, void *mlx_ptr);

/* ------ mouse_up.c ------------------------------------------------------- */
int		mouse_up(int button, void *mlx_ptr);

/* ------ mouse_move.c ------------------------------------------------------- */
void	mouse_move(t_mlx *mlx);

/* ------ main_raycasting.c ------------------------------------------------ */
void	raycasting(t_mlx *mlx, int need_free);

#endif