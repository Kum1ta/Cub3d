/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:42:54 by psalame           #+#    #+#             */
/*   Updated: 2024/04/14 13:22:09 by psalame          ###   ########.fr       */
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
		dprintf(2, "Error: %s\n", errval);
	exit(1);
}

void	server_loop_hook(int sockfd, t_client *clients)
{
	int			i;
	char		*request;
	int			byteRead;
	long long	currentTs;

	try_accept_client(sockfd, clients);
	i = 0;
	currentTs = current_timestamp();
	while (i < SV_MAX_CONNECTION)
	{
		if (clients[i].socket != -1)
		{
			request = read_request(clients[i].socket, &byteRead, false);
			if (byteRead == -1 && errno != EAGAIN)
				ft_dprintf(2, "Error while receiving packet of %s: %s.\n", clients[i].ip, strerror(errno));
			else
			{
				if (request != NULL)
				{
					printf("received request of %s: '%s'.\n", clients[i].ip, request);
					manage_client_request(clients, i, request, currentTs);
				}
				if (byteRead == 0)
					remove_client(clients, i);
				else if (currentTs - clients[i].last_ping > 40000 )
				{
					printf("Disconnecting %s: timed out.\n", clients[i].ip);
					remove_client(clients, i);
				}
			}
			free(request);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		sockfd;
	struct	sockaddr_in addr;
	t_client	clients[SV_MAX_CONNECTION];
	char	*ip;

	if (ac > 1)
		ip = av[1];
	else
		ip = SV_IP;
	if (!create_socket(&sockfd))
		error_socket(strerror(errno), sockfd, NULL);
	if (inet_aton(ip, &(addr.sin_addr)) == 0)
		error_socket(ip, sockfd, "Error: invalid address %s\n");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SV_PORT);
	if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
		error_socket(strerror(errno), sockfd, NULL);
	if (listen(sockfd, SV_MAX_CONNECTION) != 0)
		error_socket(strerror(errno), sockfd, NULL);
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	init_clients_tab(clients);
	printf("Server is now listening on '%s:%d'\n", ip, SV_PORT);
	while (1)
	{
		server_loop_hook(sockfd, clients);
		usleep(100);
	}
}