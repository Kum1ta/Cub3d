/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:20:08 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 18:54:16 by psalame          ###   ########.fr       */
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
		ft_lstclear(&(mlx->keyboard), NULL);
	}
	free(mlx);
	return (1);
}