/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/17 19:02:58 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

float raycast(t_mlx *mlx, float angle)
{
    float distance = 0.0;

    while (distance < MAX_DISTANCE)
	{
        float posX = mlx->map->playerPos.x + distance * cos(angle);
        float posY = mlx->map->playerPos.y + distance * sin(angle);
        int tileX = (int)(posX / TILE_SIZE);
        int tileY = (int)(posY / TILE_SIZE);
        if (mlx->map->blocks[tileX][tileY] == WALL)
		{
            float deltaX = posX - mlx->map->playerPos.x;
            float deltaY = posY - mlx->map->playerPos.y;
            distance = sqrt(deltaX * deltaX + deltaY * deltaY);
            break;
        }

        distance += 0.01;
    }

    return distance;
}

void	raycasting(t_mlx *mlx, int need_free)
{
	float		angle[WIDTH];
	float		distance[WIDTH];
	static void	*img = NULL;

	if (img)
		mlx_destroy_image(mlx->mlx, img);
	if (need_free)
		return ;
	img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	for (int i = 0; i < WIDTH; i++)
	{
		angle[i] = mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV;
		distance[i] = raycast(mlx, angle[i]);
		// if (distance[i] < 0.1)
		// 	distance[i] = 0.1;
		// if (distance[i] > MAX_DISTANCE)
		// 	continue;
	}
	mini_map(mlx, angle, distance, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	// exit(0);
}
