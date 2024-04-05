/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:42:26 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 17:34:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_MENU_H
# define MAIN_MENU_H

# include "../graphics.h"

void	create_square(t_mlx *mlx, void *img);
void	add_button(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int));

char	*start_solo_game(void *ptr, int action);
char	*open_multiplayer_menu(void *ptr, int action);
char	*open_main_menu(void *ptr, int action);
char	*set_ip_address_btn(void *ptr, int action);
char	*set_port_btn(void *ptr, int action);
char	*connect_btn(void *ptr, int action);

#endif