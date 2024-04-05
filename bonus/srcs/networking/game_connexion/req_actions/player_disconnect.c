/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_disconnect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:03:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 13:10:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

static inline int	cmp_ply(void *plyRaw, void *srcRaw)
{
	t_online_player	*player;
	int				src;

	player = plyRaw;
	src = (int) srcRaw;
	return (player->serverId - src);
}

void	player_disconnect(t_server *srv, char *value, void *mlx)
{
	int	player_src;

	(void) mlx;
	player_src = ft_atoi(value);
	ft_lstremoveif(&srv->online_player, (void *) player_src, &free, &cmp_ply);
}
