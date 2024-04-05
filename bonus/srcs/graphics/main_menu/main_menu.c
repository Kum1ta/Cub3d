/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:01 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 17:20:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

typedef struct s_main_menu
{
	t_img	logo;
}	t_main_menu;

void	create_square(t_mlx *mlx, void *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 30)
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0x5F0FF000);
			j++;
		}
		i++;
	}
}

void	add_button(t_mlx *mlx, int xy[3], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + 190 && mlx->mouse->y > xy[1] - 30 && mlx->mouse->y < xy[1] + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, xy[0] - 10, xy[1] - 22);
		if (mlx->mouse->pressed_left)
		{
			mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
			f((void *)mlx, 1);
			mlx->menu_button_focus = (intptr_t) f((void *)mlx, 2);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[01], 0xFFFFFFFF, f((void *)mlx, 0));
}

void	main_menu(t_mlx *mlx, int need_free)
{
	static 	t_main_menu *main_menu = NULL;
	static	void		*square_img = NULL;
	static	int			loaded = 0;

	if (need_free)
	{
		if (main_menu && main_menu->logo.img)
			mlx_destroy_image(mlx->mlx, main_menu->logo.img);
		free(main_menu);
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
		loaded = 0;
		return ;
	}
	if (!loaded)
	{
		start_screen(mlx, 1);
		main_menu = malloc(sizeof(t_main_menu));
		if (!main_menu)
			return ;
		main_menu->logo.img = mlx_png_file_to_image(mlx->mlx, "textures/main_menu/logo.png",
				&main_menu->logo.width, &main_menu->logo.height);
		if (!main_menu->logo.img)
			return ;
		square_img = mlx_new_image(mlx->mlx, 200, 30);
		if (!square_img)
			return ;
		create_square(mlx, square_img);
		loaded = 1;
	}
	put_fps(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, main_menu->logo.img, 15 / 2, -250);
	add_button(mlx, (int [2]){50, HEIGHT / 2 - 50}, square_img, start_solo_game);
	add_button(mlx, (int [2]){50, HEIGHT / 2}, square_img, open_multiplayer_menu);
	// add_button(mlx, "Options", 50, HEIGHT / 2 + 50, square_img);
	// add_button(mlx, "Exit", 50, HEIGHT / 2 + 100, square_img);
}
