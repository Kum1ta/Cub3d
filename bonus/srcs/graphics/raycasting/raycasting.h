/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/19 13:05:11 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 1000
# define MAX_HEIGHT 10

typedef struct s_ray
{
	int		pos_x;
	int		pos_y;
	float	dir_x;
	float	dir_y;
	t_vec2	dist;
	t_vec2	delta_dist;
	int		step_x;
	int		step_y;
	int		nb_step;
	int		dir;
	int		curr_size;
}	t_ray;

/* ---- mini_map.c ---------------------------------------------------------- */
void		mini_map(t_mlx *mlx);

/* ---- inventory.c --------------------------------------------------------- */
void		inventory(t_mlx *mlx, int need_free);

/* ---- item_effect.c ------------------------------------------------------- */
void		item_effect(t_mlx *mlx, t_sprite center_sprite);

/* ---- put_actual_weapon.c ------------------------------------------------- */
void		put_actual_item(t_mlx *mlx);

/* ---- supersampling.c ----------------------------------------------------- */
int			get_ss_color(t_mlx *mlx, int x, int y, int distance);

/* ---- draw_wall_line.c ---------------------------------------------------- */
void		scalling(t_raydata *ray, t_mlx *mlx, int i);

/* ---- draw_sprites.c ------------------------------------------------------ */
t_sprite	draw_sprites(t_mlx *mlx, t_raydata **ray);

/* ---- popup.c ------------------------------------------------------------- */
void		show_popup(t_mlx *mlx);

#endif