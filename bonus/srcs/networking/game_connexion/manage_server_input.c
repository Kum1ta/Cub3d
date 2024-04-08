/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_server_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:19:30 by psalame           #+#    #+#             */
/*   Updated: 2024/04/08 20:48:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

static inline void	exec_req_action(t_server *srv, char *request, void *mlx)
{
	const char	*actionsId[] = {"sendMessage:", "playerDisconnect:", "setPlayerAttr:", "setPlayerPos:", "setDoorState:", NULL};
	const		t_req_action_fct	act_fct[] = {&receive_message, &player_disconnect, &set_player_attr, &set_player_pos, &set_door_state};
	size_t		act_len;
	int			act_i;

	if (request[0] == 0)
		return ;
	act_i = 0;
	while (actionsId[act_i])
	{
		act_len = ft_strlen(actionsId[act_i]);
		if (ft_strncmp(actionsId[act_i], request, act_len) == 0)
		{
			act_fct[act_i](srv, request + act_len, mlx);
			return ;
		}
		act_i++;
	}
	ft_dprintf(2, "Unknown request type received.\n");
}

void	manage_server_request(t_server *srv, char *request, void *mlx)
{
	char	**requestData;
	int		i;

	requestData = ft_split(request, ';'); 
	if (requestData)
	{
		i = 0;
		while (requestData[i])
		{
			exec_req_action(srv, requestData[i], mlx);
			i++;
		}
		free_split(requestData, 0);
	}
}
