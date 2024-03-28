/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/29 00:43:26 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 10000
# define MAX_RENDER_DISTANCE 40
# define FOV 80
# define PRECISION 0

typedef struct s_raydata
{
	float	dist;
	int		dir; // 0: north, 1: east, 2: south, 3: west
	float	imgXPercent;
	bool	found;
	
}	t_raydata;

/* ---- mini_map.c --------------------------------------------------------- */
void	mini_map(t_mlx *mlx, float angle[WIDTH], float distance[WIDTH], int need_free);

/* ---- inventory.c --------------------------------------------------------- */
void	inventory(t_mlx *mlx, void *img, int need_free);

#endif