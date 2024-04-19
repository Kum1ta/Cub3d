/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/19 13:08:16 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

void	receive_message(t_server *srv, char *value, void *mlx)
{
	int				from_src;
	t_online_player	*from_ply;
	char			*player_name;
	char			*popup_str;

	(void)mlx;
	from_src = ft_atoi(value);
	while (ft_isdigit(*(value++)))
		;
	from_ply = get_player_from_source(srv->online_player, from_src);
	player_name = NULL;
	if (from_ply)
		player_name = from_ply->player_name;
	else
		player_name = "???";
	popup_str = ft_strjoin(player_name, value);
	if (popup_str)
		add_popup(srv, popup_str);
}
