/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 18:26:05 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	keyboard_status(int key_code[2], bool *key, bool from, bool to)
{
	if (key_code[0] == key_code[1] && from == true && to == false)
		*key = false;
	else if (key_code[0] == key_code[1] && from == false && to == true)
		*key = true;
}

int	keyboard_down(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (key == 43 && mlx->actuel_menu == GAME)
		mlx->actuel_menu = MAP_LARG_MENU;
	else if (key == 43 && mlx->actuel_menu == MAP_LARG_MENU)
		mlx->actuel_menu = GAME;
	for (int i = 0; i < 26; i++)
		keyboard_status((int [2]){key, 4 + i}, &mlx->keyboard->a + i, false, true);
	keyboard_status((int [2]){key, 82}, &mlx->keyboard->up, false, true);
	keyboard_status((int [2]){key, 81}, &mlx->keyboard->down, false, true);
	keyboard_status((int [2]){key, 80}, &mlx->keyboard->left, false, true);
	keyboard_status((int [2]){key, 79}, &mlx->keyboard->right, false, true);
	keyboard_status((int [2]){key, 41}, &mlx->keyboard->esc, false, true);
	keyboard_status((int [2]){key, 98}, &mlx->keyboard->nb0, false, true);
	for (int i = 0; i < 9; i++)
		keyboard_status((int [2]){key, 89 + i}, &mlx->keyboard->nb1 + i, false, true);
	keyboard_status((int [2]){key, 42}, &mlx->keyboard->backspace, false, true);
	return (0);
}

int	keyboard_up(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	for (int i = 0; i < 26; i++)
		keyboard_status((int [2]){key, 4 + i}, &mlx->keyboard->a + i, true, false);
	keyboard_status((int [2]){key, 82}, &mlx->keyboard->up, true, false);
	keyboard_status((int [2]){key, 81}, &mlx->keyboard->down, true, false);
	keyboard_status((int [2]){key, 80}, &mlx->keyboard->left, true, false);
	keyboard_status((int [2]){key, 79}, &mlx->keyboard->right, true, false);
	keyboard_status((int [2]){key, 41}, &mlx->keyboard->esc, true, false);
	keyboard_status((int [2]){key, 98}, &mlx->keyboard->nb0, true, false);
	for (int i = 0; i < 9; i++)
		keyboard_status((int [2]){key, 89 + i}, &mlx->keyboard->nb1 + i, true, false);
	keyboard_status((int [2]){key, 42}, &mlx->keyboard->backspace, true, false);
	printf("%d\n", key);
	return (0);
}

int	keyboard(t_mlx *mlx)
{
	if (mlx->keyboard->esc)
		window(0, (void *)mlx);
	if (mlx->actuel_menu == GAME)
		game_keyboard(mlx);
	else if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map_keyboard(mlx);
	return (0);
}
