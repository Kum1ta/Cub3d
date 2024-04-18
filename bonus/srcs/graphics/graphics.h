/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:53 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 15:00:49 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "cub3d.h"
# include "enum_keys.h"
# include "../networking/game_connexion/game_connexion.h"

# define TIME_PER_FRAME_US 0
# define PI 3.14159265

# define WHITE 0xFFFFFFFF

typedef struct s_raydata
{
	float	img_x_percent;
	bool	found;
	t_block	*block;
	float	dist;
	int		dir;
	int		wall_start;
	int		wall_size;
	int		wall_end;
	int		diff;
	t_vec2	pos;
}	t_raydata;

typedef enum e_menu
{
	MAIN_MENU,
	MULTIPLAYER_MENU,
	MAP_LARG_MENU,
	GAME,
	OPTIONS,
	OPTIONS_LM,
	START_GAME,
	DEAD_SCREEN,
	WAIT_QUIT,
	NOTHING,
}	t_menu;

typedef enum e_inventory
{
	WEAPON_INV,
	KNIFE_INV,
	FIST_INV,
}	t_inventory;

typedef enum e_selected
{
	NOT_SELECTED,
	SELECTED,
}	t_selected;

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
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	t_img	door;
	t_img	weapon_inv;
	t_img	fist_inv;
	t_img	knife_inv;
	t_img	weapon_game;
	t_img	knife_game;
	t_img	fire_gun;
	t_img	player[4];
	t_img	health_kit;
}	t_loadeds_textures;

typedef struct s_player
{
	int					health;
	t_inventory			actual_weapon;
	int					ammo;
	int					xy_item[2];
	bool				is_reloading;
}	t_player;

typedef struct s_settings_window
{
	int		diff;
	bool	show_fps;
	int		width;
	int		height;
	int		quality;
	int		anti_aliasing;
	int		show_mini_map;
	int		pos_mini_map;
	int		texture;
	int		sensibility_x;
	int		sensibility_y;
}	t_settings_window;

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
	int					menu_button_focus;
	t_list				*keyboard;
	void				*tmp;
	t_server			game_server;
	int					just_try;
	t_settings			*stg;
	t_settings_window	stg_win;
}	t_mlx;

typedef struct s_sprite
{
	enum
	{
		NONE,
		SPRT_PLAYER,
		SPRT_HEALTH_KIT
	} e_type;
	union
	{
		t_online_player	*player;
		t_health_kit	*kit;
	} u_data;
	float	dist;
	float	depth;
	int		screen_x;
	int		screen_size[2];
	t_img	*txt;
}	t_sprite;

/* ------ main_graphics.c -------------------------------------------------- */
int			window(int event, void *mlx_ptr);

/* ------ draw_image_to_window.c ------------------------------------------- */
void		draw_image_to_window(t_mlx *mlx, t_img *img,
				const int pos[2], int size[2]);

/* ------ update.c --------------------------------------------------------- */
int			update(void *mlx_ptr);

/* ------ init.c ----------------------------------------------------------- */
int			init(t_mlx *mlx, t_map *map, t_settings *settings);

/* ------ larg_map.c ------------------------------------------------------- */
int			add_case_lm(t_mlx *mlx, int pos[4], char *str, int list[3]);
void		init_button_lm(t_mlx *mlx, t_selected (*selected)[22], int *init);
void		larg_map(t_mlx *mlx, int need_free);

/* ------ load_textures.c -------------------------------------------------- */
int			load_textures(t_mlx *mlx);

/* ------ free_all.c ------------------------------------------------------- */
int			free_all_graphics(t_mlx *mlx);

/* ------ destroy_textures.c ----------------------------------------------- */
int			destroy_textures(t_mlx *mlx);

/* ------ keyboard.c ------------------------------------------------------- */
int			keyboard_down(int key, void *mlx_ptr);
int			keyboard_up(int key, void *mlx_ptr);
int			keyboard(t_mlx *mlx);
void		set_key_not_just_down(t_list *keyboard, int key);

/* ------ gane_keyboard.c -------------------------------------------------- */
void		game_keyboard(t_mlx *mlx);

/* ------ map_larg_menu_keyboard.c ----------------------------------------- */
void		larg_map_keyboard(t_mlx *mlx);

/* ------ mouse_wheel.c ---------------------------------------------------- */
int			mouse_whell(int button, void *mlx_ptr);

/* ------ mouse_down.c ----------------------------------------------------- */
int			mouse_down(int button, void *mlx_ptr);

/* ------ mouse_up.c ------------------------------------------------------- */
int			mouse_up(int button, void *mlx_ptr);

/* ------ mouse_move.c ----------------------------------------------------- */
void		mouse_move(t_mlx *mlx);

/* ------ main_raycasting.c ------------------------------------------------ */
void		raycasting(t_mlx *mlx, int need_free);
t_raydata	*raycast(t_mlx *mlx, int screen_x, bool catch_interract,
				t_vec3 start);

/* ------ main_menu.c ------------------------------------------------------ */
void		main_menu(t_mlx *mlx, int need_free);

/* ------ multiplayer_menu.c ----------------------------------------------- */
void		multiplayer_menu(t_mlx *mlx, int need_free);

/* ------ options_menu.c --------------------------------------------------- */
void		options_menu(t_mlx *mlx, int need_free);

/* ------ start_screen.c --------------------------------------------------- */
void		start_screen(t_mlx *mlx, int need_free);

/* ------ dead_screen.c ---------------------------------------------------- */
void		dead_screen(t_mlx *mlx, int need_free);

/* ------ key_down_type.c -------------------------------------------------- */
bool		is_key_just_down(t_list *keyboard, int key);
bool		is_key_down(t_list *keyboard, int key);

/* ----- inventory.c ------------------------------------------------------- */
void		inventory(t_mlx *mlx, int need_free);

/* ----- options_menu.c ---------------------------------------------------- */
void		options_menu(t_mlx *mlx, int need_free);

#endif