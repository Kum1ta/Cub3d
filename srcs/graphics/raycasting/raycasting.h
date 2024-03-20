/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 14:37:21 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 10
# define TILE_SIZE 64
# define FOV 90

/* ---- mini_map.c --------------------------------------------------------- */
void	mini_map(t_mlx *mlx, float angle[WIDTH], float distance[WIDTH], int need_free);

/* ---- inventory.c --------------------------------------------------------- */
void	inventory(t_mlx *mlx, void *img, int need_free);

#endif