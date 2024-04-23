/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_list_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:51 by psalame           #+#    #+#             */
/*   Updated: 2024/04/23 17:45:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites_Int.h"

static inline int	count_sprites(t_mlx *mlx)
{
	int		nb;
	t_list	*online_players;
	t_list	*kits;

	nb = 0;
	if (mlx->game_server.status == CONNECTED)
	{
		online_players = mlx->game_server.online_player;
		while (online_players)
		{
			nb++;
			online_players = online_players->next;
		}
		kits = mlx->game_server.kits;
		while (kits)
		{
			nb++;
			kits = kits->next;
		}
	}
	return (nb);
}

static inline void	fill_sprite_list(t_mlx *mlx, t_sprite *lst)
{
	int			i;
	t_list		*online_players;
	t_list		*kits;

	i = 0;
	online_players = mlx->game_server.online_player;
	while (online_players)
	{
		lst[i].u_data.player = online_players->content;
		lst[i].dist = get_distance_between_2dcoords(mlx->map->player_pos,
				lst[i].u_data.player->pos);
		lst[i++].e_type = SPRT_PLAYER;
		online_players = online_players->next;
	}
	kits = mlx->game_server.kits;
	while (kits)
	{
		lst[i].u_data.kit = kits->content;
		lst[i].dist = get_distance_between_2dcoords(mlx->map->player_pos,
				lst[i].u_data.kit->pos);
		lst[i++].e_type = SPRT_HEALTH_KIT;
		kits = kits->next;
	}
	lst[i].e_type = NONE;
}

t_sprite	*get_sprite_list(t_mlx *mlx)
{
	t_sprite	*res;

	res = malloc((count_sprites(mlx) + 1) * sizeof(t_sprite));
	if (!res)
		return (NULL);
	if (mlx->game_server.status == CONNECTED)
		fill_sprite_list(mlx, res);
	else
		res->e_type = NONE;
	return (res);
}
