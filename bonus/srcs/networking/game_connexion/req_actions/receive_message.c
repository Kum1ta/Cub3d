/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 12:59:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

void	receive_message(t_server *srv, char *value, void *mlx)
{
	int				from_src;
	t_online_player	*from_ply;
	char			*player_name;

	(void) mlx;
	from_src = ft_atoi(value);
	while (ft_isdigit(*(value++)))
		;
	from_ply = get_player_from_source(from_src);
	player_name = NULL;
	if (from_ply)
		player_name = from_ply->playerName;
	ft_printf("Received message from %s (%d) : '%s'\n", player_name, from_src, value);
}
