/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:12:38 by psalame           #+#    #+#             */
/*   Updated: 2024/04/20 16:00:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

void	set_player_attr(t_server *srv, char *value, void *mlx)
{
	int				src;
	t_online_player	*ply;
	int				i;
	char			*popup_str;

	(void)mlx;
	src = ft_atoi(value);
	while (*value++ != ',')
		;
	ply = get_player_from_source(srv->online_player, src);
	while (ply == NULL && "lol fuck your cpu if i dont have ram")
		ply = create_online_player(&(srv->online_player), src);
	i = 0;
	while (i < SV_MAX_PLAYER_NAME && *value != ',')
		ply->player_name[i++] = *value++;
	ply->player_name[i] = 0;
	while (*value++ != ',')
		;
	ply->pos = parse_vec3(&value);
	ply->dir = parse_vec2(&value);
	ply->health = ft_atoi(value);
	popup_str = ft_strjoin(ply->player_name, " joined the server.");
	if (popup_str)
		add_popup(srv, popup_str);
}

void	set_player_pos(t_server *srv, char *value, void *mlx)
{
	t_online_player	*ply;

	(void)mlx;
	ply = get_player_from_source(srv->online_player, ft_atoi(value));
	if (ply)
	{
		while (*value++ != ',')
			;
		ply->pos = parse_vec3(&value);
	}
}

void	set_player_dir(t_server *srv, char *value, void *mlx)
{
	t_online_player	*ply;

	(void)mlx;
	ply = get_player_from_source(srv->online_player, ft_atoi(value));
	if (ply)
	{
		while (*value++ != ',')
			;
		ply->dir = parse_vec2(&value);
	}
}

void	set_player_health(t_server *srv, char *value, void *mlx)
{
	t_online_player	*ply;

	(void)mlx;
	ply = get_player_from_source(srv->online_player, ft_atoi(value));
	if (ply)
	{
		while (*value++ != ',')
			;
		ply->health = ft_atoi(value);
	}
}
