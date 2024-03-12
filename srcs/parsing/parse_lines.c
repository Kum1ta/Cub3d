/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:49:54 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 23:36:07 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"
#include <errno.h>

static inline void	print_map_error(t_map_error_type type)
{
	if (type == MAP_ERROR_ALLOC)
		ft_dprintf(2, "Error\n%s\n", strerror(ENOMEM));
	else if (type == MAP_INVALID_IDENTIFIER)
		ft_dprintf(2, "Error\nInvalid element identifier.\n");
	else if (type == MAP_INVALID_COLOR)
		ft_dprintf(2, "Error\nInvalid element color.\n");
	else if (type == MAP_DUPLICATE_PARAMETER)
		ft_dprintf(2, "Error\nDuplicate element identifier.\n");
	else if (type == MAP_INVALID_CHARACTER)
		ft_dprintf(2, "Error\nInvalid character in map content.\n");
	else if (type == MAP_DUPLICATE_PLAYER_POS)
		ft_dprintf(2, "Error\nDuplicate player.\n");
}

t_map_error_type	add_map_line(char *line, t_list **map_lines)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
		return (MAP_ERROR_ALLOC);
	ft_lstadd_back(map_lines, node);
	return (MAP_NO_ERROR);
}

static inline bool	check_line_content(char *line, t_map *map_data, t_list **map_lines)
{
	t_map_error_type	res;

	if (*map_lines != NULL)
		res = add_map_line(line, map_lines);
	else
		res = check_map_param(line, map_data, map_lines);
	print_map_error(res);
	return (res == MAP_NO_ERROR);
}

bool	parse_lines(int fd, t_map *map_data)
{
	char				*line;
	t_list				*map_lines;
	t_map_error_type	res;

	map_lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!check_line_content(line, map_data, map_lines))
		{
			get_next_line(-1);
			ft_lstclear(&map_lines, &free);
			return (false);
		}
		line = get_next_line(fd);
	}
	if (!map_lines)
		return (false);
	res = check_map_lines(map_data, map_lines);
	ft_lstfree(map_lines);
	if (res != MAP_NO_ERROR)
		print_map_error(res);
	return (res == MAP_NO_ERROR);
}
