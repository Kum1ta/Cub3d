/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/29 20:40:01 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 10000
# define FOV 80
# define SHOW_FPS 1 // 0: off, 1: on
# define ANTIALIASING_LEVEL 8 // 1: None, 2: 2x, 4: 4x, 8: 8x
# define QUALITY 1 // 0: high, 1: medium, 2: low
typedef struct s_raydata
{
	float	imgXPercent;
	bool	found;
	float	dist;
	int		dir; // 0: north, 1: east, 2: south, 3: west
	int		wall_start;
	int		wall_size;
	int		wall_end;
	int		diff;
	
}	t_raydata;

/* ---- mini_map.c --------------------------------------------------------- */
void	mini_map(t_mlx *mlx, float angle[WIDTH], float distance[WIDTH], int need_free);

/* ---- inventory.c --------------------------------------------------------- */
void	inventory(t_mlx *mlx, void *img, int need_free);

#endif