/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:00:22 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 00:26:40 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

static void	add_button_map(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + mlx->stg->width - 140 - 5 && mlx->mouse->y > xy[1] - 20 && mlx->mouse->y < xy[1] + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, xy[0] - 10, xy[1] - 22);
		if (mlx->mouse->pressed_left)
			f((void *)mlx, 1);
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[1], 0xFFFFFFFF, f((void *)mlx, 0));
}

void	solo_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static void	*bg = NULL;
	int			tmp[2];

	if (need_free)
	{
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
		if (bg)
			mlx_destroy_image(mlx->mlx, bg);
		return ;
	}
	if (!square_img)
	{
		square_img = mlx_new_image(mlx->mlx, mlx->stg->width - 140, 30);
		create_square(mlx, square_img, mlx->stg->width - 140, 30);
	}
	if (!bg)
	{
		bg = mlx_png_file_to_image(mlx->mlx, "textures/main_menu/bg_main_menu.png", &tmp[0], &tmp[1]);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 32);
	mlx_string_put(mlx->mlx, mlx->win, 50, 100, 0xFFFFFFFF, "Argument map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	add_button_map(mlx, (int [2]){70, 150}, square_img, argument_map);

	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 32);
	mlx_string_put(mlx->mlx, mlx->win, 50, 225, 0xFFFFFFFF, "Defaults maps");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	add_button_map(mlx, (int [2]){70, 275}, square_img, default_map1);
	add_button_map(mlx, (int [2]){70, 315}, square_img, default_map2);
	add_button_map(mlx, (int [2]){70, 355}, square_img, default_map3);

	add_button(mlx, (int [2]){mlx->stg->width - 100, mlx->stg->height - 30}, square_img, open_main_menu);
}
