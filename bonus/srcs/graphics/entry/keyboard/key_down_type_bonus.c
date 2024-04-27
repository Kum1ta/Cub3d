/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down_type_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:32:23 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

bool	is_key_down(t_list *keyboard, int key)
{
	while (keyboard)
	{
		if (key == labs((intptr_t) keyboard->content))
			return (true);
		keyboard = keyboard->next;
	}
	return (false);
}

bool	is_key_just_down(t_list *keyboard, int key)
{
	while (keyboard)
	{
		if (key == (intptr_t) keyboard->content)
		{
			set_key_not_just_down(keyboard, key);
			return (true);
		}
		keyboard = keyboard->next;
	}
	return (false);
}
