/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:56:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/16 20:51:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

void	close_server(t_server *srv, enum e_server_status status)
{
	srv->status = status;
	read_request(srv->sockfd, NULL, true);
	if (srv->sockfd > 2)
	{
		close(srv->sockfd);
		srv->sockfd = 0;
	}
	ft_lstclear(&(srv->online_player), &free);
	clear_popup(srv, true);
}

bool	client_loop_hook(t_server *srv, void *mlx)
{
	char			*request;
	int				byte_read;
	static time_t	last_ping = 0;

	request = read_request(srv->sockfd, &byte_read, false);
	if (byte_read == -1 && errno != EAGAIN)
		ft_dprintf(2, "Error while receiving packet from server: %s.\n",
			strerror(errno));
	else
	{
		if (request != NULL)
			manage_server_request(srv, request, mlx);
		if (byte_read == 0)
		{
			close_server(srv, DISCONNECTED);
			ft_printf("Disconnected from server.\n");
			return (false);
		}
	}
	free(request);
	if (time(NULL) - last_ping > 30)
		dprintf(srv->sockfd, "ping:%lld;", current_timestamp());
	if (time(NULL) - last_ping > 30)
		last_ping = time(NULL);
	return (true);
}

void	connect_to_server(t_server *srv)
{
	srv->popup = NULL;
	srv->port = ft_atoi(srv->port_str);
	if (!create_socket(&(srv->sockfd)))
	{
		close_server(srv, ERR_CREATE_SOCKET);
		return ;
	}
	srv->addr.sin_family = AF_INET;
	srv->addr.sin_port = htons(srv->port);
	if (inet_aton(srv->ip, &(srv->addr.sin_addr)) == 0)
	{
		close_server(srv, ERR_INVALID_ADDRESS);
		return ;
	}
	if (connect(srv->sockfd, (struct sockaddr *) &(srv->addr),
			sizeof(srv->addr)) != 0)
	{
		close_server(srv, ERR_FAILED_CONNEXION);
		return ;
	}
	fcntl(srv->sockfd, F_SETFL, O_NONBLOCK);
	srv->status = CONNECTED;
}
