/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:44:30 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/19 12:49:55 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

int	*return_good_int(t_settings *settings, char *line)
{
	if (!ft_strcmp("width", line))
		return (&settings->width);
	else if (!ft_strcmp("height", line))
		return (&settings->height);
	else if (!ft_strcmp("quality", line))
		return (&settings->quality);
	else if (!ft_strcmp("antialiasing", line))
		return (&settings->antialiasing);
	else if (!ft_strcmp("show_minimap", line))
		return (&settings->show_minimap);
	else if (!ft_strcmp("minimap_pos", line))
		return (&settings->minimap_pos);
	else if (!ft_strcmp("show_fps", line))
		return (&settings->show_fps);
	else if (!ft_strcmp("sensibility_x", line))
		return (&settings->sensibility_x);
	else if (!ft_strcmp("sensibility_y", line))
		return (&settings->sensibility_y);
	else if (!ft_strcmp("texture", line))
		return (&settings->texture);
	return (NULL);
}

void	*create_default_config(char *path)
{
	int			fd;

	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (error_config("Can't create config file", NULL));
	ft_putstr_fd("width=1024\
\nheight=768\
\nquality=1\
\nantialiasing=1\
\nshow_minimap=1\
\nminimap_pos=0\
\nshow_fps=1\
\nsensibility_x=50\
\nsensibility_y=50\
\ntexture=0\n", fd);
	close(fd);
	return (path);
}

void	init_settings(t_settings *settings)
{
	settings->width = -1;
	settings->height = -1;
	settings->quality = -1;
	settings->antialiasing = -1;
	settings->show_minimap = -1;
	settings->minimap_pos = -1;
	settings->show_fps = -1;
	settings->texture = -1;
	settings->sensibility_x = -1;
	settings->sensibility_y = -1;
}

t_settings	*verification_settings(t_settings *settings)
{
	if (settings->width < 800 || settings->width > 1920
		|| settings->height < 600 || settings->height > 1080
		|| settings->quality < 1 || settings->quality > 10
		|| settings->antialiasing < 1 || settings->antialiasing > 8
		|| settings->show_minimap < 0 || settings->show_minimap > 1
		|| settings->minimap_pos < 0 || settings->minimap_pos > 2
		|| settings->show_fps < 0 || settings->show_fps > 1
		|| settings->texture < 0 || settings->texture > 1
		|| settings->sensibility_x < 0 || settings->sensibility_x > 200
		|| settings->sensibility_y < 0 || settings->sensibility_y > 200)
	{
		free(settings);
		return (error_config("Error in config file", NULL));
	}
	return (settings);
}

t_settings	*parse_config_file(char *path)
{
	t_settings	*settings;

	if ((access(path, F_OK) == -1 && create_default_config(path) == NULL)
		|| access(path, R_OK))
		return (error_ptr("Can't read config file", NULL));
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (error_config("Error malloc", NULL));
	init_settings(settings);
	settings = parse_config(path, settings);
	get_next_line(-1);
	if (!settings)
		return (NULL);
	settings = verification_settings(settings);
	if (!settings)
		return (NULL);
	settings->minimap_pos_x = 25;
	settings->minimap_pos_y = 25;
	if (settings->minimap_pos == 1)
		settings->minimap_pos_x = settings->width - 375;
	else if (settings->minimap_pos == 2)
		settings->minimap_pos_y = settings->height - 225;
	return (settings);
}
