/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_kit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:07 by psalame           #+#    #+#             */
/*   Updated: 2024/04/25 13:14:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server_Int_bonus.h"

void	act_add_health_kit(t_server *srv, int clientI, char *value)
{
	t_list			*node;
	t_health_kit	*kit;
	int				i;

	(void) value;
	node = malloc(sizeof(t_list) + sizeof(t_health_kit));
	if (!node)
		return ;
	kit = (void *)node + sizeof(t_list);
	node->content = kit;
	kit->pos = srv->clients[clientI].player_pos;
	kit->id = srv->kit_id++;
	node->next = srv->kits;
	srv->kits = node;
	i = -1;
	while (++i < SV_MAX_CONNECTION)
		if (srv->clients[i].socket != -1)
			dprintf(srv->clients[i].socket, "addHealthKit:%d,%.2f,%.2f,%.2f;",
				kit->id, kit->pos.x, kit->pos.y, kit->pos.z);
}

static inline int	cmp_kit_id(void *kit, void *id)
{
	return (((t_health_kit *)kit)->id != (intptr_t) id);
}

void	act_take_health_kit(t_server *srv, int clientI, char *value)
{
	intptr_t	id;
	int			i;

	id = ft_atoi(value);
	ft_lstremoveif(&srv->kits, (void *) id, NULL, &cmp_kit_id);
	i = -1;
	while (++i < SV_MAX_CONNECTION)
		if (srv->clients[i].socket != -1)
			dprintf(srv->clients[i].socket, "removeHealthKit:%d,%s;",
				clientI, value);
}
