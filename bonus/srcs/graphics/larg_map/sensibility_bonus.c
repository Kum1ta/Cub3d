/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sensibility_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:24:00 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

static inline void	draw_circle(t_mlx *mlx, int x, int y, int radius)
{
	int	i;
	int	j;
	int	dist;

	i = 0;
	while (i < 2 * radius)
	{
		j = 0;
		while (j < 2 * radius)
		{
			dist = (radius - i) * (radius - i) + (radius - j) * (radius - j);
			if (dist <= radius * radius)
				mlx_pixel_put(mlx->mlx, mlx->win,
					x + i - radius, y + j - radius, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

static inline void	draw_line(t_mlx *mlx, int x, int y, int size)
{
	while (size >= 0)
		mlx_pixel_put(mlx->mlx, mlx->win, x + size--, y, 0xFFFFFFFF);
}

void	btn_scroll(t_mlx *mlx, int x, int y, int *edit_value)
{
	const int	radius = 10;
	int			mouse_pos[2];

	mlx_mouse_get_pos(mlx->mlx, mouse_pos, mouse_pos + 1);
	if (mlx->mouse->pressed_left
		&& mouse_pos[0] >= x + *edit_value - radius
		&& mouse_pos[0] <= x + *edit_value + radius
		&& mouse_pos[1] >= y - radius && mouse_pos[1] <= y + radius)
	{
		*edit_value = mouse_pos[0] - x;
		if (*edit_value < 0)
			*edit_value = 0;
		else if (*edit_value > 200)
			*edit_value = 200;
	}
	draw_circle(mlx, x + *edit_value, y, radius);
	draw_line(mlx, x, y, 200);
}
