/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:08 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/19 18:25:28 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	free_all_graphics(t_mlx *mlx)
{
	if (mlx)
	{
		free(mlx->menu_map);
		free(mlx->mouse);
		free(mlx->map);
		free(mlx->player);
		free(mlx->keyboard);
	}
	free(mlx);
	return (1);
}