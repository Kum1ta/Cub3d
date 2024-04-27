/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:01 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	create_square(t_mlx *mlx, void *img, int width, int height)
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

void	add_button(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + 190
		&& mlx->mouse->y > xy[1] - 30 && mlx->mouse->y < xy[1] + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			img, xy[0] - 10, xy[1] - 22);
		if (mlx->mouse->pressed_left)
		{
			f((void *)mlx, 1);
			mlx->menu_button_focus = (intptr_t) f((void *)mlx, 2);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[01], 0xFFFFFFFF,
		f((void *)mlx, 0));
}

void	init_main_menu(t_mlx *mlx, int *loaded, void **bg, void **square_img)
{
	int	tmp;

	start_screen(mlx, 1);
	*square_img = mlx_new_image(mlx->mlx, 200, 30);
	if (!*square_img)
		return ;
	create_square(mlx, *square_img, 200, 30);
	tmp = 0;
	*bg = mlx_png_file_to_image(mlx->mlx,
			"textures/main_menu/bg_main_menu.png", &tmp, loaded);
	if (!bg)
		return ;
	*loaded = 1;
}

void	free_main_menu(t_mlx *mlx, void *bg, void *square_img, int *loaded)
{
	if (square_img)
		mlx_destroy_image(mlx->mlx, square_img);
	*loaded = 0;
	if (bg)
		mlx_destroy_image(mlx->mlx, bg);
	return ;
}

void	main_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static void	*bg = NULL;
	static int	loaded = 0;

	if (need_free)
	{
		free_main_menu(mlx, bg, square_img, &loaded);
		return ;
	}
	if (!loaded)
		init_main_menu(mlx, &loaded, &bg, &square_img);
	put_fps(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 128);
	mlx_string_put(mlx->mlx, mlx->win, 50, 200, 0xFFFFFFFF, "Kumilos");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	add_button(mlx, (int [2]){50, mlx->stg->height / 2 - 50},
		square_img, open_solo_menu);
	add_button(mlx, (int [2]){50, mlx->stg->height / 2},
		square_img, open_multiplayer_menu);
	add_button(mlx, (int [2]){50, mlx->stg->height / 2 + 50},
		square_img, open_settings_menu);
	add_button(mlx, (int [2]){50, mlx->stg->height / 2 + 100},
		square_img, exit_button);
}
