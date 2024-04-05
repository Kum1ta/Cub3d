/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:35:21 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 17:25:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main_menu.h"

void	multiplayer_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static bool	loaded = false;

	if (need_free)
	{
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
	}
	if (!loaded)
	{
		square_img = mlx_new_image(mlx->mlx, 200, 30);
		if (!square_img)
			return ;
		create_square(mlx, square_img);
		loaded = true;
	}
	put_fps(mlx, 0);
	add_button(mlx, (int [2]){50, HEIGHT / 2 - 75}, square_img, set_ip_address_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 - 25}, square_img, set_port_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 + 25}, square_img, connect_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 + 75}, square_img, open_main_menu);
}


