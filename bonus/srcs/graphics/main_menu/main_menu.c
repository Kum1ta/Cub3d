/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:01 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 21:22:16 by edbernar         ###   ########.fr       */
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

void	main_menu(t_mlx *mlx, int need_free)
{
	static 	t_main_menu *main_menu;
	static	int	loaded = 0;

	if (need_free)
	{
		put_video(mlx, 1);
		if (main_menu->logo.img)
			mlx_destroy_image(mlx->mlx, main_menu->logo.img);
		free(main_menu);
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
		loaded = 1;
	}
	put_fps(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, main_menu->logo.img, 15 / 2, -250);
}
