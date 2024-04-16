/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/16 21:00:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

void	receive_message(t_server *srv, char *value, void *mlx)
{
	int				from_src;
	t_online_player	*from_ply;
	char			*player_name;
	char			*popup_str;

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
