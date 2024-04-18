/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:42:26 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 17:33:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_MENU_H
# define MAIN_MENU_H

# include "../graphics.h"

# define A_NUM 1
# define A_POINT 2
# define A_ALPHA 4

void	add_button(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int));
void	create_square(t_mlx *mlx, void *img, int width, int height);

char	*open_solo_menu(void *ptr, int action);
char	*open_multiplayer_menu(void *ptr, int action);
char	*open_main_menu(void *ptr, int action);
char	*set_ip_address_btn(void *ptr, int action);
char	*set_port_btn(void *ptr, int action);
char	*set_pseudo_btn(void *ptr, int action);
char	*connect_btn(void *ptr, int action);
char	*open_settings_menu(void *ptr, int action);
char	*exit_button(void *ptr, int action);

#endif