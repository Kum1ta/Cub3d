/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:27:23 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 23:28:16 by psalame          ###   ########.fr       */
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

static inline void	*get_param_ptr(char *identifier, t_map *map_data, int *type)
{
	*type = 0;
	if (ft_strmcmp(identifier, "NO", 3) == 0)
		return (&(map_data->texture.north));
	else if (ft_strncmp(identifier, "SO", 3) == 0)
		return (&(map_data->texture.south));
	else if (ft_strncmp(identifier, "EA", 3) == 0)
		return (&(map_data->texture.east));
	else if (ft_strncmp(identifier, "WE", 3) == 0)
		return (&(map_data->texture.west));
	else
	{
		*type = 1;
		if (ft_strncmp(identifier, "C", 2) == 0)
			return (&(map_data->texture.ceiling));
		else if (ft_strncmp(identifier, "F", 2) == 0)
			return (&(map_data->texture.floor));
		else
			return (NULL);
	}
}

static bool	set_map_color_param(int color[3], char *color_str)
{
	int	current;

	current = 0;
	while (*color_str)
	{
		if (!ft_isdigit(*color_str) && *color_str != ',')
			return (false);
		if (*color_str == ',')
		{
			if (current == 2 || color[current] == -1)
				return (false);
			else
				current++;
		}
		else
		{
			color[current] = ft_atoi(color_str);
			if (color[current] > 255)
				return (false);
			while (ft_isdigit(*color_str))
				color_str++;
		}
		color_str++;
	}
	return (color[2] != -1);
}


static t_map_error_type	set_map_param(char **data, t_map *map_data)
{
	void	*param_ptr;
	int		param_type;

	param_ptr = get_param_ptr(data[0], map_data, &param_type);
	if (param_ptr == NULL)
		return (MAP_INVALID_IDENTIFIER);
	if (param_type == 0)
	{
		if (*((char **)param_ptr) != NULL)
			return (MAP_DUPLICATE_PARAMETER);
		*((char **)param_ptr) = ft_strdup(data[1]);
		if (*((char **)param_ptr) == NULL)
			return (MAP_ERROR_ALLOC);
	}
	else
	{
		if ((*((int **)param_ptr))[0] != -1)
			return (MAP_DUPLICATE_PARAMETER);
		if (ft_strlen(data[1]) > 11)
			return (MAP_INVALID_COLOR);
		if (!set_map_color_param(*((int **)param_ptr), data[1]))
			return (MAP_INVALID_COLOR);
	}
	return (MAP_NO_ERROR);
}

t_map_error_type	check_map_param(char *line, t_map *map_data, t_list **map_lines)
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
		data = ft_split2(line, WHITESPACE_CHARS);
		if (data != NULL)
		{
			if (data[1] == NULL || data[3] == NULL)
				valid = MAP_INVALID_IDENTIFIER;
			else
				valid = set_map_param(data, map_data);
			free_split(data, false);
		}
		else
			valid = MAP_ERROR_ALLOC;
	}
	free(line);
	return (valid);
}
