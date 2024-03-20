/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 01:43:53 by edbernar         ###   ########.fr       */
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

void	put_actual_weapon(t_mlx *mlx, void *img)
{
	int	i;

	i = -1;
	while (++i < 20)
		mlx_set_image_pixel(mlx->mlx, img, WIDTH / 2 - 10 + i, HEIGHT / 2, 0xFF00FF00);
	i = -1;
	while (++i < 20)
		mlx_set_image_pixel(mlx->mlx, img, WIDTH / 2, HEIGHT / 2 - 10 + i, 0xFF00FF00);
	if (mlx->player->actual_weapon == WEAPON_INV)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->weapon_game->img, 0, 0);
	// else if (mlx->player->actual_weapon == FIST_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->fist_inv->img, 0, 0);
	// else if (mlx->player->actual_weapon == KNIFE_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->knife_inv->img, 0, 0);
}

void	play_sound(t_mlx *mlx)
{
	static int	i = 0;
	static long long last_time = 0;

	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"play_sound()\" : Forbidden fonction\n\033[0m");
		i++;
	}
	if (mlx->player->actual_weapon == WEAPON_INV && mlx->mouse->pressed_left && get_now_time() - last_time > 125000)
	{
		system("paplay ./sounds/game/weapon_fire.wav &");
		last_time = get_now_time();
	}
	// else if (mlx->player->actual_weapon == FIST_INV)
	// 	system("afplay ./sounds/fist.wav &");
	// else if (mlx->player->actual_weapon == KNIFE_INV)
	// 	system("afplay ./sounds/knife.wav &");
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
	play_sound(mlx);
	// put_actual_weapon(mlx, img);
	// mini_map(mlx, angle, distance, 0);
	// inventory(mlx, img, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	// exit(0);
}
