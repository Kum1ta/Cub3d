/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:53 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/14 18:26:33 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "cub3d.h"

# define WIDTH 1900
# define HEIGHT 950

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

typedef struct s_mlx
{
	t_mouse		*mouse;
	t_map		*map;
	t_menu_map	*menu_map;
	void    	*mlx;
	void    	*win;
	void		*img;
	t_menu		actuel_menu;
}   t_mlx;

/* ------ map.c ------------------------------------------------------------ */
void	larg_map(t_mlx *mlx);

/* ------ free_all.c ------------------------------------------------------- */
void	free_all_graphics(t_mlx *mlx);

/* ------ keyboard.c ------------------------------------------------------- */
int		keyboard(int key, void *mlx_ptr);

/* ------ mouse_wheel.c ---------------------------------------------------- */
int		mouse_whell(int button, void *mlx_ptr);

/* ------ mouse_down.c ----------------------------------------------------- */
int		mouse_down(int button, void *mlx_ptr);

/* ------ mouse_up.c ------------------------------------------------------- */
int		mouse_up(int button, void *mlx_ptr);

#endif