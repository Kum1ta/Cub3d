/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:42:54 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 19:36:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"

void	error_socket(char *errval, int sockfd, char *special_err_msg)
{
	if (sockfd != -1)
		close(sockfd);
	if (special_err_msg)
		dprintf(2, special_err_msg, errval);
	else
		dprintf(2, "\aError: %s\n", errval);
	exit(1);
}

static inline void	catch_client_request(t_server *srv, int i)
{
	int		byte_read;
	char	*request;

	request = read_request(srv->clients[i].socket, &byte_read, false);
	if (byte_read == -1 && errno != EAGAIN)
		ft_dprintf(2, "\aError while receiving packet of %s: %s.\n",
			srv->clients[i].ip, strerror(errno));
	else
	{
		if (request != NULL)
			manage_client_request(srv, i, request);
		if (byte_read == 0)
			remove_client(srv->clients, i);
		else if (srv->current_ts - srv->clients[i].last_ping > 40000)
		{
			printf("Disconnecting %s: timed out.\n", srv->clients[i].ip);
			remove_client(srv->clients, i);
		}
	}
	free(request);
}

static inline void	server_loop_hook(t_server *srv)
{
	int			i;

	srv->current_ts = current_timestamp();
	try_accept_client(srv);
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (srv->clients[i].socket != -1)
			catch_client_request(srv, i);
		i++;
	}
	usleep(100);
}

int	main(int ac, char **av)
{
	struct sockaddr_in	addr;
	char				*ip;
	t_server			srv;

	if (ac > 1)
		ip = av[1];
	else
		ip = SV_IP;
	if (!create_socket(&srv.sockfd))
		error_socket(strerror(errno), srv.sockfd, NULL);
	if (inet_aton(ip, &(addr.sin_addr)) == 0)
		error_socket(ip, srv.sockfd, "Error: invalid address %s\n");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SV_PORT);
	if (bind(srv.sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
		error_socket(strerror(errno), srv.sockfd, NULL);
	if (listen(srv.sockfd, SV_MAX_CONNECTION) != 0)
		error_socket(strerror(errno), srv.sockfd, NULL);
	fcntl(srv.sockfd, F_SETFL, O_NONBLOCK);
	init_clients_tab(srv.clients);
	printf("Server is now listening on '%s:%d'\n", ip, SV_PORT);
	srv.kit_id = 0;
	srv.kits = NULL;
	while (1)
		server_loop_hook(&srv);
}
