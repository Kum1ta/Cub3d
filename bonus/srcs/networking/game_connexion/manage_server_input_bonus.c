/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_server_input_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:19:30 by psalame           #+#    #+#             */
/*   Updated: 2024/04/25 13:03:50 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

static inline void	exec_req_action(t_server *srv, char *request, void *mlx)
{
	const char				*actions_id[] = {"sendMessage:",
		"playerDisconnect:", "setPlayerAttr:", "setPlayerPos:", "setPlayerDir:",
		"setDoorState:", "shoot:", "cut:", "setHealth:", "addHealthKit:",
		"removeHealthKit:", NULL};
	const t_req_action_fct	act_fct[] = {&receive_message, &player_disconnect,
		&set_player_attr, &set_player_pos, &set_player_dir, &set_door_state,
		&act_shoot, &act_cut, &set_player_health, &add_health_kit,
		&remove_health_kit};
	size_t					act_len;
	int						act_i;

	if (request[0] == 0)
		return ;
	act_i = 0;
	while (actions_id[act_i])
	{
		act_len = ft_strlen(actions_id[act_i]);
		if (ft_strncmp(actions_id[act_i], request, act_len) == 0)
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
	char	**request_data;
	int		i;

	request_data = ft_split(request, ';');
	if (request_data)
	{
		i = 0;
		while (request_data[i])
		{
			exec_req_action(srv, request_data[i], mlx);
			i++;
		}
		free_split(request_data, 0);
	}
}
