/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_online_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:30:15 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 14:11:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

t_online_player	*create_online_player(int server_id)
{
	t_online_player	*res;
	t_list			*node;

	printf("creating player %d\n", server_id); // debug
	res = malloc(sizeof(t_online_player));
	if (!res)
		return (NULL);
	node = ft_lstnew(res);
	if (!node)
	{
		free(res);
		return (NULL);
	}
	res->serverId = server_id;
	return (res);
}
