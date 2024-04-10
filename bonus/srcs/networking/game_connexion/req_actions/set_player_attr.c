/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:12:38 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 17:14:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

static t_vec3	parse_vec3(char *str)
{
	t_vec3	res;

	res.x = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.y = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.z = ft_atof(str);
	// printf("vec3 res : %f, %f, %f\n", res.x, res.y, res.z);
	return (res);
}

void	set_player_attr(t_server *srv, char *value, void *mlx)
{
	int				src;
	t_online_player	*ply;
	int				i;

	src = ft_atoi(value);
	while (*value++ != ',')
		;
	ply = get_player_from_source(srv->online_player, src);
	while (ply == NULL && "lol fuck your cpu if i dont have ram")
		ply = create_online_player(&(srv->online_player), src);
	i = 0;
	while (i < SV_MAX_PLAYER_NAME && *value != ',')
		ply->playerName[i++] = *value++;
	ply->playerName[i] = 0;
	while (*value++ != ',')
		;
	ply->pos = parse_vec3(value);
}

void	set_player_pos(t_server *srv, char *value, void *mlx)
{
	t_online_player	*ply;

	ply = get_player_from_source(srv->online_player, ft_atoi(value));
	if (ply)
	{
		while (*value++ != ',')
			;
		ply->pos = parse_vec3(value);
	}
}
