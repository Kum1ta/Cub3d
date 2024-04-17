/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:14 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 14:36:35 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"

void	init_clients_tab(t_client *clients)
{
	int	i;

	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		clients[i].socket = -1;
		i++;
	}
}

bool	add_client(t_client *clients, int clientSock, char ip[INET_ADDRSTRLEN])
{
	int	i;

	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (clients[i].socket == -1)
		{
			fcntl(clientSock, F_SETFL, O_NONBLOCK);
			clients[i].socket = clientSock;
			strcpy(clients[i].ip, ip);
			clients[i].player_name[0] = 0;
			clients[i].last_ping = current_timestamp();
			return (true);
		}
		i++;
	}
	return (false);
}

void	remove_client(t_client *clients, int clientI)
{
	int	i;

	if (clients[clientI].socket != -1)
	{
		close(clients[clientI].socket);
		read_request(clients[clientI].socket, NULL, true);
		clients[clientI].socket = -1;
		printf("Client %s disconnected.\n", clients[clientI].ip);
		i = -1;
		while (++i < SV_MAX_CONNECTION)
			if (clients[i].socket != -1)
				ft_dprintf(clients[i].socket, "playerDisconnect:%d;", clientI);
	}
}

void	try_accept_client(int sockfd, t_client *clients)
{
	int					client_sock;
	struct sockaddr_in	client_adress;
	unsigned int		addr_len;
	char				ip[INET_ADDRSTRLEN];

	addr_len = sizeof(client_adress);
	client_sock = accept(sockfd, (struct sockaddr *) &client_adress, &addr_len);
	if (client_sock != -1)
	{
		inet_ntop(AF_INET, &(client_adress.sin_addr), ip, INET_ADDRSTRLEN);
		if (!add_client(clients, client_sock, ip))
		{
			ft_printf("Can't connect %s: server is full.\n", ip);
			close(client_sock);
		}
		else
			ft_printf("Client %s connected.\n", ip);
	}
}
