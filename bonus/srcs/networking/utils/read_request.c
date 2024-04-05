/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:36:04 by psalame           #+#    #+#             */
/*   Updated: 2024/04/04 18:12:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdbool.h>
#include <time.h>

#ifndef BUFFER_READ_SIZE
# define BUFFER_READ_SIZE 200
#endif

static void	set_prev_buffer(char **request, char **prev_buffer)
{
	size_t	req_len;
	char	*last_sep;

	if (!request || !*request)
		return ;
	req_len = ft_strlen(*request);
	if (req_len > 0 && (*request)[req_len - 1] != ';')
	{
		last_sep = ft_strrchr(*request, ';');
		if (last_sep == NULL)
		{
			*prev_buffer = *request;
			*request = NULL;
		}
		else
		{
			last_sep[0] = 0;
			*prev_buffer = ft_strdup(last_sep + 1);
		}
	}
}



char	*read_request(int socketfd, int *byteRead, bool clear)
{
	char		*request;
	char		buffer[BUFFER_READ_SIZE + 1];
	static char	*prev_buffer[1024];

	if (socketfd > 1024)
		return (NULL);
	request = NULL;
	if (prev_buffer[socketfd])
		request = prev_buffer[socketfd];
	prev_buffer[socketfd] = NULL;
	if (clear)
		free(request);
	if (clear)
		return (NULL);
	do
	{
		*byteRead = read(socketfd, buffer, BUFFER_READ_SIZE);
		buffer[*byteRead] = 0;
		if (*byteRead > 0)
			request = ft_strfjoin(request, buffer);
	} while (*byteRead > 0);
	set_prev_buffer(&request, prev_buffer + socketfd);
	return (request);
}
