/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:11:43 by psalame           #+#    #+#             */
/*   Updated: 2024/04/12 16:57:58 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"
#include "../../../graphics/graphics.h"
#define MAX_SHOOT_DIST_SOUND 100.0f
#define MAX_CUT_DIST_SOUND 5.0f

static void	play_sound_dist(char *sound_path, float volume_percent)
{
	char		*sound_volume;
	char		*cmd;

	if (volume_percent < 1)
		return ;
	if (volume_percent > 100.0f)
		volume_percent = 100.0f;
	sound_volume = ft_itoa(USHRT_MAX * (volume_percent / 100));
	// system("paplay --volume=50000 ./sounds/game/weapon_reload.wav &");
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
	origin = parse_vec3(value);
	dist = get_distance_between_2dcoords(origin, mlx->map->playerPos);
	play_sound_dist("./sounds/game/weapon_fire.wav", 1.0f / ((float)(dist + 1) / MAX_SHOOT_DIST_SOUND));
	if (got_touch && mlx->player->health > 0)
	{
		mlx->player->health = mlx->player->health - 10;
		if (mlx->player->health < 0)
			mlx->player->health = 0;
		ft_dprintf(srv->sockfd, "setHealth:%d;", mlx->player->health);
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
	origin = parse_vec3(value);
	dist = get_distance_between_2dcoords(origin, mlx->map->playerPos);
	play_sound_dist("./sounds/game/cut_hit.wav", 1.0f / ((float)(dist + 1) / MAX_CUT_DIST_SOUND));
	if (got_touch && mlx->player->health > 0)
	{
		mlx->player->health = 0;
		ft_dprintf(srv->sockfd, "setHealth:%d;", mlx->player->health);
	}
}
