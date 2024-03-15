/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:53 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 23:27:43 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "cub3d.h"

# define WIDTH 1900
# define HEIGHT 950
# define TIME_PER_FRAME_US 0

typedef enum e_menu {
	MAIN_MENU,
	MAP_LARG_MENU,
	GAME,
	OPTIONS,
}	t_menu;

typedef struct s_mouse
{
	int		x;
	int		y;
	bool	pressed_left;
	bool	pressed_right;
}	t_mouse;

typedef struct s_menu_map
{
	int		x;
	int		y;
	int		size;
}	t_menu_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef	struct s_loadeds_textures
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
	t_img	*floor;
	t_img	*ceiling;
	t_img	*player_icon_larg_map;
}	t_loadeds_textures;

typedef struct s_keyboard
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	esc;
}	t_keyboard;

typedef struct s_mlx
{
	t_mouse				*mouse;
	t_map				*map;
	t_menu_map			*menu_map;
	t_loadeds_textures	*textures;
	void    			*mlx;
	void    			*win;
	t_menu				actuel_menu;
	t_keyboard			*keyboard;
}   t_mlx;

/* ------ main_graphics.c -------------------------------------------------- */
int		close_window(int event, void *mlx_ptr);

/* ------ map.c ------------------------------------------------------------ */
void	larg_map(t_mlx *mlx, int need_free);

/* ------ load_textures.c -------------------------------------------------- */
int		load_textures(t_mlx *mlx);

/* ------ free_all.c ------------------------------------------------------- */
void	free_all_graphics(t_mlx *mlx);

/* ------ destroy_textures.c ----------------------------------------------- */
int		destroy_textures(t_mlx *mlx);

/* ------ keyboard.c ------------------------------------------------------- */
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

/* ------ main_raycasting.c ------------------------------------------------ */
void	raycasting(t_mlx *mlx);

#endif