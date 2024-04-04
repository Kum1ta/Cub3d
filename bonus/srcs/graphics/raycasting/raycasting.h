/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/04 14:25:27 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 1000
# define WALL_SIZE 1.0
# define FOV 60
# define SHOW_FPS 1 // 0: off, 1: on
# define ANTIALIASING_LEVEL 1 // 1: None, 2: 2x, 4: 4x, 8: 8x
# define QUALITY 1 // 1: high, 2: medium, 3: low

# define POS_MINI_MAP_X 10
# define POS_MINI_MAP_Y HEIGHT - 210
# define WALL_SIZE_MINI_MAP 20

/* ---- mini_map.c --------------------------------------------------------- */
void	mini_map(t_mlx *mlx);

/* ---- inventory.c --------------------------------------------------------- */
void	inventory(t_mlx *mlx, void *img, int need_free);

#endif