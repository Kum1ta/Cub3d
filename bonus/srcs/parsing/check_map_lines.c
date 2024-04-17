/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:38:20 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 17:26:07 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

static bool	is_all_lines_valid(t_list *lines)
{
	char	*line;
	bool	prev_line_empty;
	bool	current_line_empty;

	prev_line_empty = false;
	while (lines)
	{
		line = lines->content;
		current_line_empty = true;
		while (line && *line)
		{
			if (ft_strchr("0123456789 NSWED\n", *line) == NULL)
				return (false);
			if (current_line_empty && !ft_isspace(*line))
				current_line_empty = false;
			if (*line == '\n')
				*line = 0;
			line++;
		}
		lines = lines->next;
		if (!current_line_empty && prev_line_empty)
			return (false);
		prev_line_empty = current_line_empty;
	}
	return (true);
}

static size_t	get_max_line_size(t_list *lines)
{
	size_t	max;
	size_t	current_size;
	size_t	i;
	char	*line;

	max = 0;
	while (lines)
	{
		current_size = 0;
		i = 0;
		line = lines->content;
		while (line[i])
		{
			if (line[i] != ' ')
				current_size = i + 1;
			i++;
		}
		if (current_size > max)
			max = current_size;
		lines = lines->next;
	}
	return (max);
}

static size_t	get_map_height(t_list *lines)
{
	size_t	height;
	char	*str;

	height = 0;
	while (lines)
	{
		str = lines->content;
		while (*str)
			if (!ft_isspace(*str++))
				break ;
		if (*str == 0)
			break ;
		height++;
		lines = lines->next;
	}
	return (height);
}

static bool	allocate_map(t_map *map)
{
	size_t	i;

	map->blocks = malloc((map->height + 1) * sizeof(t_block *));
	if (!map->blocks)
		return (false);
	i = 0;
	while (i < map->height)
	{
		map->blocks[i] = ft_calloc((map->width + 1), sizeof(t_block));
		if (map->blocks[i] == NULL)
		{
			free_blocks(map->blocks);
			map->blocks = NULL;
			return (false);
		}
		map->blocks[i][map->width].type = END;
		i++;
	}
	map->blocks[i] = NULL;
	return (true);
}

t_map_error_type	check_map_lines(t_map *map, t_list *lines, int screen_res[2])
{
	t_map_error_type	res;
	bool				*flagBlocks;

	if (!is_all_lines_valid(lines))
		return (MAP_INVALID_CHARACTER);
	map->width = get_max_line_size(lines);
	map->height = get_map_height(lines);
	if (!allocate_map(map))
		return (MAP_ERROR_ALLOC);
	res = set_map_blocks(map, lines, screen_res);
	if (res != MAP_NO_ERROR)
		return (res);
	if (map->player_pos.x == -1.0f)
		return (MAP_NO_ERROR);
	flagBlocks = ft_calloc((map->height + 1) * (map->width + 1), sizeof(bool));
	if (flagBlocks == NULL)
		return (MAP_ERROR_ALLOC);
	if (can_exit_map(map->blocks, flagBlocks, map->width + 1, (t_ivec2){map->player_pos.x, map->player_pos.y}))
		res = MAP_CAN_EXIT;
	free(flagBlocks);
	return (res);
}
