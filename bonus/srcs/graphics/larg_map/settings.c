/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:18:09 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 18:23:17 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

void	fill_image(t_mlx *mlx, void *img, int color, int xy[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < xy[0])
	{
		j = 0;
		while (j < xy[1])
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			j++;
		}
		i++;
	}
}

void	init_bg(t_mlx *mlx, t_img *bg, void **bg_word)
{
	*bg_word = mlx_new_image(mlx->mlx, 200, 30);
	fill_image(mlx, *bg_word, 0xEE009900, (int [2]){200, 30});
	bg->img = mlx_png_file_to_image(mlx->mlx,
			"textures/main_menu/bg_main_menu.png", &bg->width, &bg->height);
	if (!bg->img)
		return ;
}

void	put_button(t_mlx *mlx, int diff, t_img bg)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg.img, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40, 80 + mlx->stg_win.diff,
		0xFFFFFFFF, "Settings\b");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff, 0xFFFFFFFF,
		"Show fps : ");
	list_button_fps_lm(mlx, (int [2]){270, 185 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 80, 235 + diff, 0xFFFFFFFF,
		"Texture  :");
	list_button_texture_lm(mlx, (int [2]){270, 220 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 285 + diff, 0xFFFFFFFF,
		"Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 330 + diff, 0xFFFFFFFF,
		"Quality");
	list_button_quality_lm(mlx, (int [2]){90, 345 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 400 + diff, 0xFFFFFFFF,
		"Anti aliasing (SS)");
	list_button_aa_lm(mlx, (int [2]){90, 415 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 475 + diff, 0xFFFFFFFF,
		"Sensibility X");
}

void	options_menu_lm(t_mlx *mlx, int need_free)
{
	static void		*bg_word = NULL;
	static t_img	bg;
	int				diff;

	if (need_free)
	{
		if (bg_word)
			mlx_destroy_image(mlx->mlx, bg_word);
		if (bg.img)
			mlx_destroy_image(mlx->mlx, bg.img);
		return ;
	}
	if (!bg_word)
		init_bg(mlx, &bg, &bg_word);
	diff = 50;
	btn_scroll(mlx, 320, 468 + diff, &mlx->stg_win.sensibility_x);
	mlx_string_put(mlx->mlx, mlx->win, 90, 510 + diff, 0xFFFFFFFF,
		"Sensibility Y");
	put_button(mlx, diff, bg);
	btn_scroll(mlx, 320, 503 + diff, &mlx->stg_win.sensibility_y);
	add_button_lm(mlx, (int [2]){mlx->stg->width - 100,
		mlx->stg->height - 30}, bg_word, button_main_lm);
}

void	down_bar(t_mlx *mlx, int need_free)
{
	static void	*img = NULL;
	static void	*bg_word = NULL;

	if (need_free)
	{
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		if (bg_word)
			mlx_destroy_image(mlx->mlx, bg_word);
		return ;
	}
	if (!img)
	{
		img = mlx_new_image(mlx->mlx, mlx->stg->width, 100);
		fill_image(mlx, img, 0xFF212121, (int [2]){mlx->stg->width, 100});
		bg_word = mlx_new_image(mlx->mlx, 140, 30);
		fill_image(mlx, bg_word, 0xEE009900, (int [2]){140, 30});
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, mlx->stg->height - 100);
	add_button_lm(mlx, (int [2]){50, mlx->stg->height - 40},
		bg_word, button_resume_lm);
	add_button_lm(mlx, (int [2]){200, mlx->stg->height - 40},
		bg_word, button_option_lm);
	add_button_lm(mlx, (int [2]){360, mlx->stg->height - 40},
		bg_word, main_menu_lm);
}
