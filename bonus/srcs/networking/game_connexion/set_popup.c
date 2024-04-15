/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_popup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:40:44 by psalame           #+#    #+#             */
/*   Updated: 2024/04/15 19:44:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

void	set_popup(t_server *srv, char *str)
{
	free(srv->popup.str);
	srv->popup.str = str;
	srv->popup.end_at = get_now_time() + 5000000;
}
