/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:11:43 by psalame           #+#    #+#             */
/*   Updated: 2024/04/15 13:33:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"
#include "../../../graphics/graphics.h"
#define SHOOT_DIST_DECR 1500
#define CUT_DIST_DECR 5000

static void	play_sound_dist(char *sound_path, int decr)
{
	char		*sound_volume;
	char		*cmd;

	if (decr > USHRT_MAX)
		return ;
	sound_volume = ft_itoa(USHRT_MAX - decr);
	cmd = ft_strjoin("paplay --volume=", sound_volume);
	free(sound_volume);
	if (cmd)
		cmd = ft_strfjoin(cmd, " ");
	if (cmd)
		cmd = ft_strfjoin(cmd, sound_path);
	if (cmd)
		cmd = ft_strfjoin(cmd, " &");
	if (cmd)
		system(cmd);
	free(cmd);
}

void	act_shoot(t_server *srv, char *value, void *mlxRaw)
{
	int			got_touch;
	t_vec3		origin;
	float		dist;
	t_mlx		*mlx;

	mlx = mlxRaw;
	got_touch = ft_atoi(value);
	while (*value++ != ',')
		;
	origin = parse_vec3(&value);
	dist = get_distance_between_2dcoords(origin, mlx->map->playerPos);
	play_sound_dist("./sounds/game/weapon_fire.wav", dist * SHOOT_DIST_DECR);
	if (got_touch && mlx->player->health > 0)
	{
		mlx->player->health = mlx->player->health - 10;
		if (mlx->player->health < 0)
			mlx->player->health = 0;
		ft_dprintf(srv->sockfd, "setHealth:%d;", mlx->player->health);
		system("paplay --volume=20000 ./sounds/game/take_damage.mp3 &");
	}
}

void	act_cut(t_server *srv, char *value, void *mlxRaw)
{
	int			got_touch;
	t_vec3		origin;
	float		dist;
	t_mlx		*mlx;

	mlx = mlxRaw;
	got_touch = ft_atoi(value);
	while (*value++ != ',')
		;
	origin = parse_vec3(&value);
	dist = get_distance_between_2dcoords(origin, mlx->map->playerPos);
	play_sound_dist("./sounds/game/cut_hit.wav", dist * CUT_DIST_DECR);
	if (got_touch && mlx->player->health > 0)
	{
		mlx->player->health = 0;
		ft_dprintf(srv->sockfd, "setHealth:%d;", mlx->player->health);
		system("paplay --volume=20000 ./sounds/game/take_damage.mp3 &");
	}
}
