/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:01 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/04 14:22:30 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

typedef struct s_main_menu
{
	t_img	logo;
}	t_main_menu;

void	put_video(t_mlx *mlx, int need_free)
{
	static t_img	img;
	static int		frame = 0;
	char			str[50];

	if (need_free)
	{
		if (img.img)
			mlx_destroy_image(mlx->mlx, img.img);
		return ;
	}
	ft_strncpy(str, "textures/main_menu/video/1/000.png\0", 36);
	str[27] = frame / 100 + '0';
	str[28] = frame / 10 % 10 + '0';
	str[29] = frame % 10 + '0';
	if (img.img)
		mlx_destroy_image(mlx->mlx, img.img);
	img.img = mlx_png_file_to_image(mlx->mlx, str, &img.width, &img.height);
	if (!img.img)
		return ;
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	frame++;
	if (frame == 102)
		frame = 0;
}

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

void	add_bouton(t_mlx *mlx, char *str, int x, int y, void *img)
{
	if (mlx->mouse->x > x - 10 && mlx->mouse->x < x + 190 && mlx->mouse->y > y - 30 && mlx->mouse->y < y + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, x - 10, y - 22);
		if (mlx->mouse->pressed_left)
		{
			mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
			mlx->actuel_menu = GAME;
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, x, y, 0xFFFFFFFF, str);
}

void	main_menu(t_mlx *mlx, int need_free)
{
	static 	t_main_menu *main_menu;
	static	void		*square_img = NULL;
	static	int			loaded = 0;

	if (need_free)
	{
		put_video(mlx, 1);
		if (main_menu->logo.img)
			mlx_destroy_image(mlx->mlx, main_menu->logo.img);
		free(main_menu);
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
		loaded = 0;
		return ;
	}
	put_video(mlx, 0);
	if (!loaded)
	{
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
	add_bouton(mlx, "Solo", 50, HEIGHT / 2 - 50, square_img);
	add_bouton(mlx, "Multiplayer", 50, HEIGHT / 2, square_img);
	add_bouton(mlx, "Options", 50, HEIGHT / 2 + 50, square_img);
	add_bouton(mlx, "Exit", 50, HEIGHT / 2 + 100, square_img);
}
