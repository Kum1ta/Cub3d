/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 15:35:27 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

void	update_pos(t_mlx *mlx)
{
	int	dx;
	int	dy;

	if (mlx->mouse->pressed_left)
	{
		dx = mlx->mouse->x - mlx->mouse->last_x;
		dy = mlx->mouse->y - mlx->mouse->last_y;
		mlx->menu_map->x += dx;
		mlx->menu_map->y += dy;
	}
	mlx->mouse->last_x = mlx->mouse->x;
	mlx->mouse->last_y = mlx->mouse->y;
}

void	add_button_lm(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + 130
		&& mlx->mouse->y > xy[1] - 30 && mlx->mouse->y < xy[1] + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, img,
			xy[0] - 10, xy[1] - 22);
		if (mlx->mouse->pressed_left)
		{
			f((void *)mlx, 1);
			mlx->menu_button_focus = (intptr_t) f((void *)mlx, 2);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[1],
		0xFFFFFFFF, f((void *)mlx, 0));
}

void	change_config_file_lm(t_settings_window *stg)
{
	char		*tmp[2];
	int			i[2];
	const char	key[10][15] = {"show_fps=", "width=", "height=", "quality=",
		"antialiasing=", "show_minimap=", "minimap_pos=", "texture=",
		"sensibility_x=", "sensibility_y="};
	const int	value[10] = {stg->show_fps, stg->width, stg->height,
		stg->quality, stg->anti_aliasing, stg->show_mini_map,
		stg->pos_mini_map, stg->texture, stg->sensibility_x,
		stg->sensibility_y};

	i[0] = open(".config", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (i[0] == -1)
		return ;
	i[1] = -1;
	while (++i[1] < 10)
	{
		tmp[0] = ft_strdup(key[i[1]]);
		tmp[1] = ft_itoa(value[i[1]]);
		tmp[0] = ft_strjoin_gnl(tmp[0], tmp[1]);
		free(tmp[1]);
		tmp[0] = ft_strjoin_gnl(tmp[0], "\n");
		write(i[0], tmp[0], ft_strlen(tmp[0]));
		free(tmp[0]);
	}
	close(i[0]);
}

void	larg_map(t_mlx *mlx, int need_free)
{
	if (need_free)
	{
		down_bar(mlx, 1);
		options_menu_lm(mlx, 1);
		return ;
	}
	update_pos(mlx);
	fill_map(mlx);
	put_player(mlx);
	down_bar(mlx, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 14);
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 275,
		mlx->stg->height - 60, 0xFFFFFFFF, "'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 210,
		mlx->stg->height - 40, 0xFFFFFFFF, "'r' to reset the map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
}
