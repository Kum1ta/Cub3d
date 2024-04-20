/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_popup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:46:51 by psalame           #+#    #+#             */
/*   Updated: 2024/04/18 13:12:24 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static inline void	get_popup_pos_data(t_mlx *mlx, int *pos, int *pos_incr)
{
	*pos = 50;
	*pos_incr = 20;
	if (mlx->stg->show_minimap)
	{
		if (mlx->stg->minimap_pos == 0)
		{
			*pos += mlx->stg->minimap_pos_y + 200;
			*pos_incr = 20;
		}
		else if (mlx->stg->minimap_pos == 2)
		{
			*pos = mlx->stg->minimap_pos_y - *pos;
			*pos_incr = -(*pos_incr);
		}
	}
}

void	show_popup(t_mlx *mlx)
{
	t_list	*popup_node;
	t_popup	*popup_data;
	int		pos;
	int		pos_increment;

	get_popup_pos_data(mlx, &pos, &pos_increment);
	if (mlx->game_server.status == CONNECTED)
	{
		clear_popup(&mlx->game_server, false);
		popup_node = mlx->game_server.popup;
		while (popup_node)
		{
			popup_data = popup_node->content;
			mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 15.0f);
			mlx_string_put(mlx->mlx, mlx->win, 10, pos, 0xFF00FF00,
				popup_data->str);
			pos += pos_increment;
			popup_node = popup_node->next;
		}
	}
}
