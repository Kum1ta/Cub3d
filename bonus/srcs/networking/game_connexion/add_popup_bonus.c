/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_popup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:40:44 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:19 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

void	add_popup(t_server *srv, char *str)
{
	t_list	*node;
	t_popup	*popup;

	node = malloc(sizeof(t_list) + sizeof(t_popup));
	if (!node)
		return ;
	popup = ((void *) node) + sizeof(t_list);
	node->content = popup;
	node->next = srv->popup;
	srv->popup = node;
	popup->str = str;
	popup->end_at = get_now_time() + 5000000;
}

static int	popup_must_delete(void *popupRaw, void *force)
{
	t_popup	*popup;

	if ((intptr_t) force)
		return (!true);
	popup = popupRaw;
	return (!(get_now_time() >= popup->end_at));
}

static inline void	popup_free(void *popupRaw)
{
	free(((t_popup *)popupRaw)->str);
}

void	clear_popup(t_server *srv, bool force)
{
	ft_lstremoveif(&srv->popup, (void *)(intptr_t) force,
		&popup_free, &popup_must_delete);
}
