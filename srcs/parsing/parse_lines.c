/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:49:54 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 13:27:22 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

static inline bool	check_map_line(char *line, t_list **map_lines)
{
	
}

static bool	check_line_content(char *line, t_map *map_data, t_list **map_lines)
{
	if (*map_lines != NULL)
	{
		
	}
	else
	{
		
	}
}

bool	parse_lines(int fd, t_map *map_data)
{
	char	*line;
	t_list	*map_lines;

	map_lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!check_line_content(line, map_data, map_lines))
		{
			get_next_line(-1);
			return (false);
		}
		line = get_next_line(fd);
	}
	if (!map_lines)
		return (false);
	return (true);
}
