/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_to_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:19:03 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 16:29:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_image_to_window(t_mlx *mlx, t_img *img, int pos[2], int size[2])
{
	int	x;
	int	y;
	int	imgX;
	int	imgY;
	int	clr;

	x = 0;
	while (x < size[0] && x + pos[0] < mlx->stg->width)
	{
		imgX = ((float)x / (float)size[0]) * img->width;
		y = 0;
		while (y < size[1] && y + pos[1] < mlx->stg->height)
		{
			imgY = ((float)y / (float)size[1]) * img->height;
			clr = mlx_get_image_pixel(mlx->mlx, img->img, imgX, imgY);
			if (clr >> 24 & 0xFF == 0xFF && pos[0] + x >= 0 && pos[1] + y >= 0)
				mlx_pixel_put(mlx->mlx, mlx->win, pos[0] + x, pos[1] + y, clr);
			y++;
		}
		x++;
	}
}
