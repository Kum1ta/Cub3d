/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_kit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:14:44 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:13 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

void	add_health_kit(t_server *srv, char *value, void *mlx)
{
	t_list			*node;
	t_health_kit	*kit;

	(void)mlx;
	node = malloc(sizeof(t_list) + sizeof(t_health_kit));
	if (!node)
		return ;
	kit = (void *)node + sizeof(t_list);
	node->content = kit;
	node->next = srv->kits;
	srv->kits = node;
	kit->id = ft_atoi(value);
	while (*value && *value++ != ',')
		;
	kit->pos = parse_vec3(&value);
}

static inline int	cmp_kit_id(void *kit, void *id)
{
	return (((t_health_kit *)kit)->id != (intptr_t) id);
}

void	remove_health_kit(t_server *srv, char *value, void *mlx)
{
	int				ply_id;
	t_online_player	*ply;
	int				id;

	(void)mlx;
	ply_id = ft_atoi(value);
	while (*value && *value++ != ',')
		;
	id = ft_atoi(value);
	ply = get_player_from_source(srv->online_player, ply_id);
	if (ply)
		ply->health = 100;
	ft_lstremoveif(&srv->kits, (void *)(intptr_t) id, NULL, &cmp_kit_id);
}
