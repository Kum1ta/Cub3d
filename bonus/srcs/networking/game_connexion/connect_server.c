/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:56:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 10:40:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

static inline void	close_server(t_server *srv, enum e_server_status status)
{
	srv->status = status;
	read_request(srv->sockfd, NULL, true);
	if (srv->sockfd > 2)
	{
		close(srv->sockfd);
		srv->sockfd = 0;
	}

}

bool	client_loop_hook(t_server *srv, void *mlx)
{
	char			*request;
	int				byteRead;
	static time_t	last_ping = 0;

	request = read_request(srv->sockfd, &byteRead);
	if (byteRead == -1 && errno != EAGAIN)
	{
		ft_dprintf(2, "Error while receiving packet from server: %s.\n", strerror(errno));
	}
	else
	{
		if (request != NULL)
			manage_server_request(srv->sockfd, request, mlx);
		if (byteRead == 0)
		{
			close_server(srv, DISCONNECTED);
			return (false);
		}
	}
	free(request);
	if (time(NULL) - last_ping > 5)
	{
		last_ping = time(NULL);
		ft_dprintf(srv->sockfd, "ping:%lld;", current_timestamp());
	}
	return (true);
}

t_server	connect_to_server(char ip[16], uint16_t port)
{
	t_server	res;

	bzero(&res, sizeof(t_server));
	res.ip = ip;
	res.port = port;
	if (!create_socket(&(res.sockfd)))
	{
		close_server(&res, ERR_CREATE_SOCKET);
		return (res);
	}
	res.addr.sin_family = AF_INET;
	res.addr.sin_port = htons(res.port);
	if (inet_aton(res.ip, &(res.addr.sin_addr)) == 0)
	{
		close_server(&res, ERR_INVALID_ADDRESS);
		return (res);
	}
	if (connect(res.addr.sockfd, (struct sockaddr *) &(res.addr), sizeof(res.addr)) != 0)
	{
		close_server(&res, ERR_CONNECT);
		return (res);
	}
	fcntl(res.sockfd, F_SETFL, O_NONBLOCK);
	res.status = CONNECTED;
	return (res);
}
