/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 15:53:14 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"


int	keyboard(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	printf("key: %d\n", key);
	mlx = (t_mlx *)mlx_ptr;
	if (key == 41)
		close_window(0, (void *)mlx);
	return (0);
}
