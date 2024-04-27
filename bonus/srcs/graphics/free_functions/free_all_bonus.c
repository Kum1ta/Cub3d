/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:08 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	free_all_graphics(t_mlx *mlx)
{
	if (mlx)
	{
		free(mlx->menu_map);
		free(mlx->mouse);
		free(mlx->stg);
		free_map(mlx->map);
		free(mlx->player);
		ft_lstclear(&(mlx->keyboard), NULL);
	}
	free(mlx);
	return (1);
}
