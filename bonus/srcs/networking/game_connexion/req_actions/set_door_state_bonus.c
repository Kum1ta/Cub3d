/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_door_state_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:28:08 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:15 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"
#include "../../../graphics/graphics.h"

void	set_door_state(t_server *srv, char *value, void *mlxRaw)
{
	bool	state;
	int		pos_x;
	int		pos_y;
	t_mlx	*mlx;

	(void)srv;
	state = ft_atoi(value) == 1;
	pos_x = 0;
	pos_y = 0;
	while (*value && *value++ != ',')
		;
	pos_x = ft_atoi(value);
	while (*value && *value++ != ',')
		;
	pos_y = ft_atoi(value);
	mlx = mlxRaw;
	if (pos_x < 0 || pos_y < 0
		|| (size_t)pos_x >= mlx->map->width
		|| (size_t)pos_y >= mlx->map->height
		|| mlx->map->blocks[pos_y][pos_x].type != DOOR)
		return ;
	mlx->map->blocks[pos_y][pos_x].data.door = state;
}
