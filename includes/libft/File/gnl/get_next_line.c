/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:10:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/01/09 23:16:40 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static char	*fill_buffer(int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i == -1)
		buffer[0] = 1;
	else
		buffer[i] = 0;
	return (buffer);
}

static int	fill_len(char **backup, char **buffer, char **line, int fd)
{
	if (*backup)
	{
		*line = ft_strjoin_gnl(*line, *backup);
		free(*backup);
		*backup = NULL;
	}
	else
	{
		free(*buffer);
		*buffer = fill_buffer(fd);
		if (!*buffer)
			return (1);
		if ((*buffer)[0] == 1 || (*buffer)[0] == 0)
			return (2);
		*line = ft_strjoin_gnl(*line, *buffer);
		if (!*buffer || !*line)
			return (1);
	}
	if (character_pos(*line, '\n') >= 0)
	{
		*backup = ft_strdup(&(*line)[character_pos(*line, '\n') + 1]);
		(*line)[character_pos(*line, '\n') + 1] = 0;
		return (2);
	}
	return (0);
}

static char	*free_all(char **backup)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (backup[i])
			free(backup[i]);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*buffer;
	char		*line;
	int			ret;

	line = NULL;
	buffer = NULL;
	if (fd == -1)
		return (free_all(backup));
	while (1)
	{
		ret = fill_len(&backup[fd], &buffer, &line, fd);
		if (ret == 1)
			return (NULL);
		else if (ret == 2)
			break ;
	}
	if (line && line[0] == 0)
	{
		free(line);
		line = NULL;
	}
	free(buffer);
	return (line);
}
