/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_exit_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:30:49 by psalame           #+#    #+#             */
/*   Updated: 2024/04/19 13:11:58 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

t_list	*new_node_pos(int x, int y)
{
	intptr_t	pos;

	pos = (((intptr_t) x) << (4 * 8)) | ((intptr_t) y);
	return (ft_lstnew((void *) pos));
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

static inline bool	propagate_pos(t_list *lst_pos, bool *flagBlocks,
								int width, t_ivec2 pos)
{
	return (lst_add_pos(lst_pos, flagBlocks, width, (t_ivec2){pos.x + 1, pos.y})
	&& lst_add_pos(lst_pos, flagBlocks, width, (t_ivec2){pos.x - 1, pos.y})
	&& lst_add_pos(lst_pos, flagBlocks, width, (t_ivec2){pos.x, pos.y + 1})
	&& lst_add_pos(lst_pos, flagBlocks, width, (t_ivec2){pos.x, pos.y - 1}));
}

bool	can_exit_map(t_block **blocks, bool *flagBlocks, int width, t_ivec2 pos)
{
	t_list	*prev_pos;
	t_list	*lst_pos;
	bool	res;

	lst_pos = new_node_pos(pos.x, pos.y);
	if (!lst_pos)
		return (true);
	res = false;
	while (!res && lst_pos)
	{
		pos = get_node_pos(lst_pos);
		if (!blocks[pos.y] || blocks[pos.y][pos.x].type == END
			|| blocks[pos.y][pos.x].type == EMPTY
			|| ((pos.x == 0 || pos.y == 0)
				&& blocks[pos.y][pos.x].type != WALL))
			res = true;
		else if (blocks[pos.y][pos.x].type != WALL
			&& !propagate_pos(lst_pos, flagBlocks, width, pos))
			res = true;
		prev_pos = lst_pos;
		lst_pos = lst_pos->next;
		free(prev_pos);
	}
	return (res);
}
