/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:08 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 21:14:50 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	free_all_graphics(t_mlx *mlx)
{
	if (mlx)
	{
		free(mlx->menu_map);
		free(mlx->map);
		free(mlx->keyboard);
	}
	free(mlx);
	return (1);
}
