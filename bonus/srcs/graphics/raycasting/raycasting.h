/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/16 15:26:42 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 1000
# define MAX_HEIGHT 10

/* ---- mini_map.c ---------------------------------------------------------- */
void	mini_map(t_mlx *mlx);

/* ---- inventory.c --------------------------------------------------------- */
void	inventory(t_mlx *mlx, int need_free);

/* ---- draw_sprites.c ------------------------------------------------------ */
t_sprite	draw_sprites(t_mlx *mlx, t_raydata **ray);

/* ---- popup.c ------------------------------------------------------------- */
void	show_popup(t_mlx *mlx);

#endif