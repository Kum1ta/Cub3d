/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:43:52 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server_Int_bonus.h"

void	act_shoot(t_server *srv, int clientI, char *value)
{
	int	player_id;
	int	i;

	player_id = ft_atoi(value);
	while (*value++ != ',')
		;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "shoot:%d,%d,%s;",
				clientI, player_id == i, value);
		i++;
	}
}

void	act_cut(t_server *srv, int clientI, char *value)
{
	int	player_id;
	int	i;

	player_id = ft_atoi(value);
	while (*value++ != ',')
		;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "cut:%d,%d,%s;",
				clientI, player_id == i, value);
		i++;
	}
}
