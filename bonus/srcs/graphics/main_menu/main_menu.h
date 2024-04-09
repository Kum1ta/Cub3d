/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:42:26 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/08 18:44:04 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_MENU_H
# define MAIN_MENU_H

# include "../graphics.h"

void	add_button(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int));
void	create_square(t_mlx *mlx, void *img, int width, int height);

char	*open_solo_menu(void *ptr, int action);
void	solo_menu(t_mlx *mlx, int need_free);
char	*argument_map(void *ptr, int action);
char	*open_multiplayer_menu(void *ptr, int action);
char	*open_main_menu(void *ptr, int action);
char	*set_ip_address_btn(void *ptr, int action);
char	*set_port_btn(void *ptr, int action);
char	*set_pseudo_btn(void *ptr, int action);
char	*connect_btn(void *ptr, int action);
char	*default_map1(void *ptr, int action);
char	*default_map2(void *ptr, int action);
char	*default_map3(void *ptr, int action);
char	*open_settings_menu(void *ptr, int action);
char	*exit_button(void *ptr, int action);


#endif