/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:58:46 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	change_config_file(t_settings_window *stg)
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

char	*back_main_menu(void *mlx, int action)
{
	((t_mlx *)mlx)->mouse->pressed_left = 0;
	if (action == 0)
		return ("Apply");
	change_config_file(&(((t_mlx *)mlx)->stg_win));
	((t_mlx *)mlx)->actuel_menu = WAIT_QUIT;
	return (NULL);
}

void	init_options_menu(t_mlx *mlx, void **square_img, void **bg, int tmp[2])
{
	if (!*square_img)
	{
		*square_img = mlx_new_image(mlx->mlx, mlx->stg->width - 140, 30);
		create_square(mlx, *square_img, mlx->stg->width - 140, 30);
	}
	if (!*bg)
		*bg = mlx_png_file_to_image(mlx->mlx,
				"textures/main_menu/bg_main_menu.png", &tmp[0], &tmp[1]);
}

void	options_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static void	*bg = NULL;
	int			diff;
	int			tmp[2];

	if (need_free)
	{
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
		if (bg)
			mlx_destroy_image(mlx->mlx, bg);
		return ;
	}
	init_options_menu(mlx, &square_img, &bg, tmp);
	diff = 50 + mlx->stg_win.diff;
	if (bg)
		mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40,
		80 + mlx->stg_win.diff, 0xFFFFFFFF, "Settings\b");
	basics_part_settings(mlx, diff);
	graphics_part_settings(mlx, diff);
	minimap_part_settings(mlx, diff);
	add_button(mlx, (int [2]){mlx->stg->width - 100,
		mlx->stg->height - 30}, square_img, back_main_menu);
}
