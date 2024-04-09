/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_door_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:28:08 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 00:38:17 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"
#include "../../../graphics/graphics.h"

void	set_door_state(t_server *srv, char *value, void *mlxRaw)
{
	bool	state;
	int		posX;
	int		posY;
	t_mlx	*mlx;

	ft_printf("update door (%s) ");
	state = ft_atoi(value) == 1;
	posX = 0;
	posY = 0;
	while (*value && *value++ != ',')
		;
	posX = ft_atoi(value);
	while (*value && *value++ != ',')
		;
	posY = ft_atoi(value);
	mlx = mlxRaw;
	ft_printf("at pos x%d y%d : %d\n", posX, posY, state);
	if (posX < 0 || posY < 0
		|| posX >= mlx->map->width || posY >= mlx->map->height
		|| mlx->map->blocks[posY][posX].type != DOOR)
		return ;
	mlx->map->blocks[posY][posX].data.door = state;
}
