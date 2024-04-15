/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_disconnect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:03:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/15 19:48:17 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

static inline int	cmp_ply(void *plyRaw, void *srcRaw)
{
	t_online_player	*player;
	int				src;

	player = plyRaw;
	src = (intptr_t) srcRaw;
	return (player->serverId - src);
}

void	player_disconnect(t_server *srv, char *value, void *mlx)
{
	t_online_player	*player;
	int				player_src;
	char			*popup_str;

	(void) mlx;
	player_src = ft_atoi(value);
	player = get_player_from_source(srv->online_player, player_src);
	if (player)
	{
		popup_str = ft_strjoin(player->playerName, " disconnected.");
		if (popup_str)
			set_popup(srv, popup_str);
	}
	ft_lstremoveif(&srv->online_player, (void *) (intptr_t) player_src, &free, &cmp_ply);
}
