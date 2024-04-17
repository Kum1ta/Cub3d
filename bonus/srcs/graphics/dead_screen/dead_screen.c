/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:48:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 21:17:23 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	create_square_ds(t_mlx *mlx, void *img, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0x5F0FF000);
			j++;
		}
		i++;
	}
}

void	add_button_ds(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + 190
		&& mlx->mouse->y > xy[1] - 30 && mlx->mouse->y < xy[1] + 10)
	{
		xy[0] -= 10;
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, xy[0], xy[1] - 22);
		if (mlx->mouse->pressed_left)
		{
			f((void *)mlx, 1);
			mlx->menu_button_focus = (intptr_t) f((void *)mlx, 2);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[1], 0xFFFFFFFF,
		f((void *)mlx, 0));
}

char	*respwan_button(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0 || action == 2)
		return ("Respawn");
	mlx = (t_mlx *)ptr;
	mlx->player->health = 100;
	if (mlx->game_server.status == CONNECTED)
		ft_dprintf(mlx->game_server.sockfd, "setHealth:%d;",
			mlx->player->health);
	mlx->actuel_menu = GAME;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2,
		mlx->stg->height / 2);
	mlx_mouse_hide();
	return (NULL);
}

char	*exit_button_ds(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ptr;
	if (action == 0 || action == 2)
		return ("Exit");
	if (action == 1)
	{
		mlx->actuel_menu = MAIN_MENU;
		mlx->player->health = 100;
		if (mlx->game_server.status == CONNECTED)
			close_server(&(mlx->game_server), DISCONNECTED);
	}
	return (NULL);
}

void	dead_screen(t_mlx *mlx, int need_free)
{
	static void	*square = NULL;

	if (need_free)
	{
		mlx_destroy_image(mlx->mlx, square);
		return ;
	}
	if (!square)
	{
		square = mlx_new_image(mlx->mlx, 200, 30);
		create_square_ds(mlx, square, 200, 30);
	}
	mlx_string_put(mlx->mlx, mlx->win, 80,
		mlx->stg->height / 2 - 100, 0xFFFFFFFF, "You are dead");
	add_button_ds(mlx, (int [2]){90, mlx->stg->height / 2 - 50},
		square, respwan_button);
	add_button_ds(mlx, (int [2]){90, mlx->stg->height / 2 - 10},
		square, exit_button_ds);
}
