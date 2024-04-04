/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:20:11 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/04 16:59:22 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	put_video(t_mlx *mlx, int need_free)
{
	static t_img	img;
	static int		frame = 0;
	char			str[37];

	if (need_free)
	{
		if (img.img)
			mlx_destroy_image(mlx->mlx, img.img);
		return (1);
	}
	ft_strncpy(str, "textures/main_menu/video/1/000.png\0", 36);
	str[27] = frame / 100 + '0';
	str[28] = frame / 10 % 10 + '0';
	str[29] = frame % 10 + '0';
	if (img.img)
		mlx_destroy_image(mlx->mlx, img.img);
	img.img = mlx_png_file_to_image(mlx->mlx, str, &img.width, &img.height);
	if (!img.img)
		return (1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	frame++;
	return (frame == 101);
}

void	start_screen(t_mlx *mlx, int need_free)
{
	put_fps(mlx, 0);
	if (put_video(mlx, need_free) == 1)
	{
		mlx->actuel_menu = MAIN_MENU;
	}
}