/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:27:23 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 13:30:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_Int.h"
#include "cub3d.h"

static inline t_map_line_type	get_line_type(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else if (*line == '1' || *line == '0')
			return (LTYPE_MAP);
		else if (((*line == 'N' || *line == 'S') && line[1] != 'O')
			|| (*line == 'W' && line[1] != 'E')
			|| (*line == 'E' && line[1] != 'A'))
			return (LTYPE_MAP);
		else
			return (LTYPE_DATA);
		
	}
	return (LTYPE_EMPTY);
}

static inline bool	is_valid_identifier(char *identifier)
{
	if ()
}

static t_map_error_type	check_map_param(char *line, t_map *map_data, t_list **map_lines)
{
	char				**data;
	t_map_line_type		type;
	t_map_error_type	valid;

	type = get_line_type(line);
	valid = MAP_NO_ERROR;
	if (type == LTYPE_MAP)
		return (check_map_line(line, map_lines));
	else if (type == LTYPE_DATA)
	{
		data = ft_split(line, ' '); // todo remake of split with all whitespaces
		if (data != NULL)
		{
			if (data[1] == NULL || !is_valid_identifier(data[0]))
				valid = MAP_INVALID_IDENTIFIER;
			else
				{/*todo*/};
			free_split(data);
		}
		else
			valid = MAP_ERROR_ALLOC;
	}
	free(line);
	return (valid);
}
