/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 17:06:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

static int	cmp_key(void *keyRaw, void *keyCmpRaw)
{
	int	key;
	int	keyCmp;

	key = (intptr_t) keyRaw;
	keyCmp = (intptr_t) keyCmpRaw;
	return (abs(key) - keyCmp);
}

static void	set_key_not_just_down(t_list *keyboard, int key)
{
	int	key_state;

	while (keyboard)
	{
		if (key == (intptr_t) keyboard->content)
		{
			key_state = (intptr_t) keyboard->content;
			key_state = -key_state;
			keyboard->content = (void *) (intptr_t) key_state;
			break ;
		}
		keyboard = keyboard->next;
	}
}

bool	is_key_down(t_list *keyboard, int key)
{
	while (keyboard)
	{
		if (key == abs((intptr_t) keyboard->content))
			return (true);
		keyboard = keyboard->next;
	}
	return (false);
}

bool	is_key_just_down(t_list *keyboard, int key)
{
	while (keyboard)
	{
		if (key == (intptr_t) keyboard->content)
		{
			set_key_not_just_down(keyboard, key);
			return (true);
		}
		keyboard = keyboard->next;
	}
	return (false);
}

int	keyboard_down(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (key == 43 && mlx->actuel_menu == GAME)
		mlx->actuel_menu = MAP_LARG_MENU;
	else if (key == 43 && mlx->actuel_menu == MAP_LARG_MENU)
	{
		mlx->actuel_menu = GAME;
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2, mlx->stg->height / 2);
	}
	if (!is_key_down(mlx->keyboard, key))
		ft_lstadd_back(&(mlx->keyboard), ft_lstnew((void *)(intptr_t) key));
	else
		set_key_not_just_down(mlx->keyboard, key);
	return (0);
}

int	keyboard_up(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	ft_lstremoveif(&(mlx->keyboard), (void *)(intptr_t) key, NULL, &cmp_key);
	return (0);
}

int	keyboard(t_mlx *mlx)
{
	if (is_key_down(mlx->keyboard, KEY_ESC))
		window(0, (void *)mlx);
	if (mlx->actuel_menu == GAME)
		game_keyboard(mlx);
	else if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map_keyboard(mlx);
	return (0);
}
