/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:42:26 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/19 00:12:02 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_MENU_H
# define MAIN_MENU_H

# include "../graphics.h"

# define A_NUM 1
# define A_POINT 2
# define A_ALPHA 4

void	add_button(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int));
void	init_antialiasing_settings(t_mlx *mlx, t_selected selected[22]);
void	create_square(t_mlx *mlx, void *img, int width, int height);
void	init_button(t_mlx *mlx, t_selected selected[22], int *init);
void	init_quality_settings(t_mlx *mlx, t_selected selected[22]);
void	init_minimap_settings(t_mlx *mlx, t_selected selected[22]);
int		add_case(t_mlx *mlx, int pos[4], char *str, int list[3]);
void	not_selected_button(t_mlx *mlx, t_selected selected[22],
			int xy[2], int list[3]);
char	*open_multiplayer_menu(void *ptr, int action);
void	list_position_mini_map(t_mlx *mlx, int xy[2]);
void	list_bigger_resolution(t_mlx *mlx, int xy[2]);
void	list_button_resolution(t_mlx *mlx, int xy[2]);
void	graphics_part_settings(t_mlx *mlx, int diff);
void	list_button_mini_map(t_mlx *mlx, int xy[2]);
void	minimap_part_settings(t_mlx *mlx, int diff);
char	*set_ip_address_btn(void *ptr, int action);
char	*open_settings_menu(void *ptr, int action);
void	list_button_texture(t_mlx *mlx, int xy[2]);
void	basics_part_settings(t_mlx *mlx, int diff);
void	list_button_quality(t_mlx *mlx, int xy[2]);
void	list_button_fps(t_mlx *mlx, int xy[2]);
char	*open_solo_menu(void *ptr, int action);
char	*open_main_menu(void *ptr, int action);
char	*set_pseudo_btn(void *ptr, int action);
void	list_button_aa(t_mlx *mlx, int xy[2]);
char	*set_port_btn(void *ptr, int action);
char	*connect_btn(void *ptr, int action);
char	*exit_button(void *ptr, int action);

#endif