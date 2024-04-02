/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:07:32 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 22:19:27 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	ajust_angle(float *angle)
{
	if (*angle < 0)
		*angle += 360;
	else if (*angle > 360)
		*angle -= 360;
}

void	free_ray(t_raydata **ray)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
		free(ray[i]);
}

void	correct_fish_eye(t_raydata *ray, float angle_ray, t_mlx *mlx)
{
	float	radian;
	float	ra;

	ra = angle_ray + 90;
	ajust_angle(&ra);
	radian = (mlx->map->playerPos.h - ra) * (PI / 180.0f);
	ray->dist *= cos(radian);
}
