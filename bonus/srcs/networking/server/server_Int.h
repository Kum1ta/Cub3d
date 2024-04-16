/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:17:24 by psalame           #+#    #+#             */
/*   Updated: 2024/04/16 20:54:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_INT_H
# define SERVER_INT_H

# include "libft.h"
# include "vector.h"
# include <stdio.h>
# include <errno.h> 
# include <string.h> 
# include <sys/socket.h>
# include <netinet/in.h>
# include <asm-generic/socket.h>
# include <fcntl.h>
# include <stdbool.h>
# include <arpa/inet.h>

# ifndef SV_IP
#  define SV_IP "127.0.0.1"
# endif

# ifndef SV_PORT
#  define SV_PORT 42420
# endif

# ifndef SV_MAX_CONNECTION
#  define SV_MAX_CONNECTION 10
# endif

# ifndef SV_MAX_PLAYER_NAME
#  define SV_MAX_PLAYER_NAME 100
# endif

typedef struct s_client
{
	int			socket;
	char		ip[INET_ADDRSTRLEN];
	char		player_name[SV_MAX_PLAYER_NAME + 1];
	char		*req_buffer;
	t_vec3		player_pos;
	t_vec2		player_dir;
	long long	last_ping;
}	t_client;

// utils
bool		create_socket(int *sockfd);
char		*read_request(int socketfd, int *byteRead, bool clear);
long long	current_timestamp(void);

// manage client
void		init_clients_tab(t_client *clients);
bool		add_client(t_client *clients,
				int clientSock,
				char ip[INET_ADDRSTRLEN]);
void		remove_client(t_client *clients, int clientI);
void		try_accept_client(int sockfd, t_client *clients);

typedef void	(*t_req_action_fct)(t_client *, int, char *, long long);

void		manage_client_request(t_client *clients,
				int clientI,
				char *request,
				long long currTs);

float		ft_atof(char *str);

#endif