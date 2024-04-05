/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:35:21 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 18:19:49 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main_menu.h"

void	catch_input(t_mlx *mlx, char *str, int max_size)
{
	int	i;
	static long long last_test = 0;
	
	if (get_now_time() - last_test < 100000)
		return ;
	last_test = get_now_time();
	if (mlx->keyboard->backspace)
	{
		if (ft_strlen(str) > 0)
			str[ft_strlen(str) - 1] = 0;
	}
	if (ft_strlen(str) < max_size)
	{
		i = 0;
		while (i < 10)
		{
			if (*((&mlx->keyboard->nb0) + i))
			{
				str[ft_strlen(str) + 1] = 0;
				str[ft_strlen(str)] = '0' + i;
			}
			i++;
		}
	}
}

int	input_btn(t_mlx *mlx)
{
	if (mlx->menu_button_focus == (intptr_t) set_ip_address_btn(NULL, 2))
	{
		catch_input(mlx, mlx->game_server.ip, 15);
	}
	else if (mlx->menu_button_focus == (intptr_t) set_port_btn(NULL, 2))
	{
		catch_input(mlx, mlx->game_server.port_str, 5);
	}
}

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
	input_btn(mlx);
}


