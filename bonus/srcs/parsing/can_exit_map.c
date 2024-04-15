/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_exit_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:30:49 by psalame           #+#    #+#             */
/*   Updated: 2024/04/15 17:32:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

t_list	*new_node_pos(int x, int y)
{
	t_list		*res;
	intptr_t	pos;

	pos = (((intptr_t) x) << (4 * 8)) | ((intptr_t) y);
	res = ft_lstnew((void *) pos);
}

t_ivec2	get_node_pos(t_list *node)
{
	t_ivec2	res;

	res.x = (((intptr_t) node->content) >> (4 * 8)) & 0xFFFFFFFF;
	res.y = (((intptr_t) node->content) & 0xFFFFFFFF);
	return (res);
}

bool	lst_add_pos(t_list *lst, bool *flagBlocks, int width, t_ivec2 pos)
{
	t_ivec2	current_pos;
	t_list	*new;

	if (flagBlocks[pos.y * width + pos.x])
		return (true);
	flagBlocks[pos.y * width + pos.x] = true;
	new = new_node_pos(pos.x, pos.y);
	if (!new)
		return (false);
	new->next = lst->next;
	lst->next = new;
	return (true);
}

bool	can_exit_map(t_block **blocks, bool *flagBlocks, int width, t_ivec2 pos)
{
	t_list	*lst_pos;
	t_list	*current_pos;
	bool	res;

	lst_pos = new_node_pos(pos.x, pos.y);
	if (!lst_pos)
		return (true);
	current_pos = lst_pos;
	res = false;
	while (!res && current_pos)
	{
		pos = get_node_pos(current_pos);
		if (!blocks[pos.y] || blocks[pos.y][pos.x].type == END || blocks[pos.y][pos.x].type == EMPTY || ((pos.x == 0 || pos.y == 0) && blocks[pos.y][pos.x].type != WALL))
			res = true;
		else if (blocks[pos.y][pos.x].type != WALL
			&& (!lst_add_pos(current_pos, flagBlocks, width, (t_ivec2){pos.x + 1, pos.y})
			|| !lst_add_pos(current_pos, flagBlocks, width, (t_ivec2){pos.x - 1, pos.y})
			|| !lst_add_pos(current_pos, flagBlocks, width, (t_ivec2){pos.x, pos.y + 1})
			|| !lst_add_pos(current_pos, flagBlocks, width, (t_ivec2){pos.x, pos.y - 1})))
			res = true;
		current_pos = current_pos->next;
	}
	ft_lstclear(&lst_pos, NULL);
	return (res);
}
