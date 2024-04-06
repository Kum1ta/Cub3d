/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:35:21 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 09:31:43 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main_menu.h"
# define A_NUM 1
# define A_POINT 1 << 1
# define A_ALPHA 1 << 2

char	get_key_ascii(int key, bool shift, int allow_char)
{
	if (key >= KEY_A && key <= KEY_Z && (allow_char & A_ALPHA) == A_ALPHA)
		return (key - KEY_A + 'a' - (' ' * shift));
	if (key == KEY_SPACE && (allow_char & A_ALPHA) == A_ALPHA)
		return (' ');
	if (key >= KEY_NB1 && key <= KEY_NB9 && (allow_char & A_NUM) == A_NUM)
		return (key - KEY_NB1 + '1');
	if (key == KEY_NB0 && (allow_char & A_NUM) == A_NUM)
		return ('0');
	if (key == KEY_POINT && (allow_char & A_POINT) == A_POINT)
		return ('.');
	return (0);
}

void	catch_input(t_mlx *mlx, char *str, int max_size, int allow_char)
{
	int		i;
	t_list	*keyboard;
	char	c;

	if (is_key_just_down(mlx->keyboard, KEY_BACKSPACE))
	{
		if (ft_strlen(str) > 0)
			str[ft_strlen(str) - 1] = 0;
	}
	keyboard = mlx->keyboard;
	while (keyboard && ft_strlen(str) < max_size)
	{
		if ((int) ((intptr_t) keyboard->content) > 0) // key just down
		{
			c = get_key_ascii((intptr_t) keyboard->content, is_key_down(mlx->keyboard, KEY_SHIFT), allow_char);
			if (c != 0)
			{
				str[ft_strlen(str) + 1] = 0;
				str[ft_strlen(str)] = c;
				keyboard->content = (void *) -((intptr_t) keyboard->content);
			}
		}
		keyboard = keyboard->next;
	}
}

int	input_btn(t_mlx *mlx)
{
	if (mlx->menu_button_focus == (intptr_t) set_ip_address_btn(NULL, 2))
		catch_input(mlx, mlx->game_server.ip, 15, A_NUM | A_POINT);
	else if (mlx->menu_button_focus == (intptr_t) set_port_btn(NULL, 2))
		catch_input(mlx, mlx->game_server.port_str, 5, A_NUM);
	else if (mlx->menu_button_focus == (intptr_t) set_pseudo_btn(NULL, 2))
	{
		catch_input(mlx, mlx->game_server.playerName,
			SV_MAX_PLAYER_NAME, A_NUM | A_POINT | A_ALPHA);
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
	add_button(mlx, (int [2]){50, HEIGHT / 2 - 100}, square_img, set_ip_address_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 - 50}, square_img, set_port_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2}, square_img, set_pseudo_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 + 50}, square_img, connect_btn);
	add_button(mlx, (int [2]){50, HEIGHT / 2 + 100}, square_img, open_main_menu);
	input_btn(mlx);
}


