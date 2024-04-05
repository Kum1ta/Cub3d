/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:36:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 15:00:04 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

char	*start_solo_game(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Start solo game");
	mlx = (t_mlx *)ptr;
	mlx->actuel_menu = GAME;
	return (NULL);
}