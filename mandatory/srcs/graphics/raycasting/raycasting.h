/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 15:40:29 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../graphics.h"

# define MAX_DISTANCE 1000
# define WALL_SIZE 1.0
# define FOV 70

typedef struct s_raydata
{
	float	imgx_percent;
	bool	found;
	float	dist;
	int		dir;
	int		wall_start;
	int		wall_size;
	int		wall_end;
	int		diff;
}	t_raydata;

typedef struct s_ray {
	float	r_angle;
	float	dirx;
	float	diry;
	int		posx;
	int		posy;
	float	distx;
	float	disty;
	float	deltadx;
	float	deltady;
	int		stepx;
	int		stepy;
	int		nbstep;
	int		dir;
}	t_ray;

/* ---- Utils -------------------------------------------------------------- */
void		correct_fish_eye(t_raydata *ray, float angle_ray, t_mlx *mlx);
void		ajust_angle(float *angle);
void		free_ray(t_raydata **ray);

/* ---- Raycast ------------------------------------------------------------ */
t_raydata	*raycast(t_mlx *mlx, float angle);

#endif