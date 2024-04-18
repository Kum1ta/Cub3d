/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:38:20 by psalame           #+#    #+#             */
/*   Updated: 2024/04/02 22:04:55 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_int.h"

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
			if (ft_strchr("01 NSWE\n", *line) == NULL)
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

static bool	can_exit_map(t_block **blocks,
	bool *flagBlocks, size_t width, t_vec2 pos)
{
	bool	escaped;

	if (blocks[pos.y] == NULL)
		return (true);
	if (blocks[pos.y][pos.x] == END || blocks[pos.y][pos.x] == EMPTY
			|| blocks[pos.y][pos.x] == WALL)
		return (blocks[pos.y][pos.x] != WALL);
	flagBlocks[pos.y * width + pos.x] = true;
	if (pos.y == 0 || pos.x == 0 || blocks[pos.y + 1] == NULL)
		return (true);
	escaped = false;
	if (!escaped && !flagBlocks[(pos.y - 1) * width + pos.x])
		escaped = can_exit_map(blocks, flagBlocks, width,
				(t_vec2){pos.x, pos.y - 1});
	if (!escaped && !flagBlocks[(pos.y + 1) * width + pos.x])
		escaped = can_exit_map(blocks, flagBlocks, width,
				(t_vec2){pos.x, pos.y + 1});
	if (!escaped && !flagBlocks[pos.y * width + pos.x - 1])
		escaped = can_exit_map(blocks, flagBlocks, width,
				(t_vec2){pos.x - 1, pos.y});
	if (!escaped && !flagBlocks[pos.y * width + pos.x + 1])
		escaped = can_exit_map(blocks, flagBlocks, width,
				(t_vec2){pos.x + 1, pos.y});
	return (escaped);
}

t_map_error_type	check_map_lines(t_map *map, t_list *lines)
{
	t_map_error_type	res;
	bool				*flag_blocks;

	if (!is_all_lines_valid(lines))
		return (MAP_INVALID_CHARACTER);
	map->width = get_max_line_size(lines);
	map->height = get_map_height(lines);
	if (!allocate_map(map))
		return (MAP_ERROR_ALLOC);
	res = set_map_blocks(map, lines);
	if (res != MAP_NO_ERROR)
		return (res);
	if (map->player_pos.x == -1.0f)
		return (MAP_NO_ERROR);
	flag_blocks = ft_calloc(map->height * map->width, sizeof(bool));
	if (flag_blocks == NULL)
		return (MAP_ERROR_ALLOC);
	if (can_exit_map(map->blocks, flag_blocks, map->width,
			(t_vec2){map->player_pos.x, map->player_pos.y}))
		res = MAP_CAN_EXIT;
	free(flag_blocks);
	return (res);
}
