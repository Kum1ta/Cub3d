/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:14 by psalame           #+#    #+#             */
/*   Updated: 2024/04/04 18:03:05 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"

void	init_clients_tab(t_client *clients)
{
	int	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		clients[i].socket = -1;
		i++;
	}
}

bool	add_client(t_client *clients, int clientSock, char ip[INET_ADDRSTRLEN])
{
	int	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (clients[i].socket == -1)
		{
			fcntl(clientSock, F_SETFL, O_NONBLOCK);
			clients[i].socket = clientSock;
			strcpy(clients[i].ip, ip);
			clients[i].playerName[0] = 0;
			clients[i].last_ping = current_timestamp();
			return (true);
		}
		i++;
	}
	return (false);
}

void	remove_client(t_client *clients, int clientI)
{
	if (clients[clientI].socket != -1)
	{
		close(clients[clientI].socket);
		read_request(clients[clientI].socket, NULL, true);
		clients[clientI].socket = -1;
		printf("Client %s disconnected.\n", clients[clientI].ip);
	}
}

void	try_accept_client(int sockfd, t_client *clients)
{
	int	clientSock;
	struct sockaddr_in	clientAdress;
	unsigned int addrLen;
	
	addrLen = sizeof(clientAdress);
	clientSock = accept(sockfd, (struct sockaddr *) &clientAdress, &addrLen);
	if (clientSock != -1)
	{
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(clientAdress.sin_addr), ip, INET_ADDRSTRLEN);
		if (!add_client(clients, clientSock, ip))
		{
			printf("Can't connect %s: server is full.\n", ip);
			close(clientSock);
		}
		else
			printf("Client %s connected.\n", ip);
	}
}
