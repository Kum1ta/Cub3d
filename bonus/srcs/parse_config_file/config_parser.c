/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:47:04 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 23:52:49 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

t_settings	*parse_config_line(t_settings *settings, char *line, int fd)
{
	int	*a;

	line[ft_strlen(line) - 1] = 0;
	if (!ft_strchr(line, '=') || is_not_digit(ft_strchr(line, '=') + 1))
		return (free_func(line, fd, settings));
	ft_strchr(line, '=')[0] = 0;
	a = return_good_int(settings, line);
	if (!a)
		return (free_func(line, fd, settings));
	line[ft_strlen(line)] = '=';
	*a = ft_atoi_s(ft_strchr(line, '=') + 1);
	return (settings);
}

t_settings	*parse_config(char *path, t_settings *settings)
{
	int			fd;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_config("Can't open config file", NULL));
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) < 2)
		{
			free(line);
			continue ;
		}
		if (!parse_config_line(settings, line, fd))
			return (NULL);
		free(line);
	}
	free(line);
	close(fd);
	return (settings);
}
