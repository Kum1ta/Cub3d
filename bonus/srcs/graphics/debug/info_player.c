/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:39:35 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/29 21:07:46 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

float only_after_point(float nombre)
{
    return (nombre - (int)nombre);
}

void	info_player(t_mlx *mlx)
{
	static int	i = 0;
	char		*tmp_str;

	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"info_player()\" : It's just for debug\n\033[0m");
		printf("\033[0;31m	info_player() : the function loses a lot of performance\n\033[0m");
		i++;
	}
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 70, 0xFFFFFFFF, "x : ");
	tmp_str = ft_itoa((int)mlx->map->playerPos.x);
	tmp_str = ft_strjoin_gnl(tmp_str, ".");
	tmp_str = ft_strjoin_gnl(tmp_str, ft_itoa(abs(only_after_point(mlx->map->playerPos.x) * 1000)));
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 200, 70, 0xFFFFFFFF, tmp_str);
	free(tmp_str);

	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 80, 0xFFFFFFFF, "y : ");
	tmp_str = ft_itoa((int)mlx->map->playerPos.y);
	tmp_str = ft_strjoin_gnl(tmp_str, ".");
	tmp_str = ft_strjoin_gnl(tmp_str, ft_itoa(abs(only_after_point(mlx->map->playerPos.y) * 1000)));
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 200, 80, 0xFFFFFFFF, tmp_str);
	free(tmp_str);

	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 90, 0xFFFFFFFF, "angle : ");
	tmp_str = ft_itoa(((int)mlx->map->playerPos.h));
	tmp_str = ft_strjoin_gnl(tmp_str, ".");
	tmp_str = ft_strjoin_gnl(tmp_str, ft_itoa((int)((mlx->map->playerPos.h - (float)((int)mlx->map->playerPos.h)) * 1000)));
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 200, 90, 0xFFFFFFFF, tmp_str);
	free(tmp_str);
}