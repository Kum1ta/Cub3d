/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:17:24 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 20:10:13 by psalame          ###   ########.fr       */
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

typedef struct s_health_kit
{
	t_vec3		pos;
	int			id;
}	t_health_kit;

typedef struct s_server
{
	int			sockfd;
	t_client	clients[SV_MAX_CONNECTION];
	long long	current_ts;
	int			kit_id;
	t_list		*kits;
}	t_server;

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
void		try_accept_client(t_server *srv);

typedef void	(*t_req_action_fct)(t_server *, int, char *);

void		manage_client_request(t_server *srv, int clientI, char *request);

float		ft_atof(char *str);

// req
void		act_init_player(t_server *srv, int client_i, char *value);
void		act_set_pos(t_server *srv, int client_i, char *value);
void		act_set_dir(t_server *srv, int client_i, char *value);
void		act_set_health(t_server *srv, int clientI, char *value);
void		act_set_door(t_server *srv, int clientI, char *value);
void		act_cut(t_server *srv, int clientI, char *value);
void		act_shoot(t_server *srv, int clientI, char *value);
void		act_add_health_kit(t_server *srv, int clientI, char *value);
void		act_take_health_kit(t_server *srv, int clientI, char *value);

#endif