/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_from_source.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:50:15 by psalame           #+#    #+#             */
/*   Updated: 2024/04/16 20:53:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

t_online_player	*get_player_from_source(t_list *players, int player_src)
{
	t_online_player	*ply;

	while (players)
	{
		ply = players->content;
		if (ply && ply->server_id == player_src)
			return (ply);
		players = players->next;
	}
	return (NULL);
}
