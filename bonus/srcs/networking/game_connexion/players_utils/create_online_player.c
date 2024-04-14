/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_online_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:30:15 by psalame           #+#    #+#             */
/*   Updated: 2024/04/14 13:29:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

t_online_player	*create_online_player(t_list **players, int server_id)
{
	t_online_player	*ply;
	t_list			*node;

	ply = malloc(sizeof(t_online_player));
	if (!ply)
		return (NULL);
	node = ft_lstnew(ply);
	if (!node)
	{
		free(ply);
		return (NULL);
	}
	ply->serverId = server_id;
	node->content = ply;
	ft_lstadd_back(players, node);
	return (ply);
}
