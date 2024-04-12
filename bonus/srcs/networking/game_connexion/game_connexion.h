/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_connexion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:25:35 by psalame           #+#    #+#             */
/*   Updated: 2024/04/12 18:08:05 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CONNEXION_H
# define GAME_CONNEXION_H
# include "cub3d.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <errno.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <stdint.h>

# ifndef SV_MAX_PLAYER_NAME
#  define SV_MAX_PLAYER_NAME 100
# endif

float		ft_atof(char *str);
long long	current_timestamp(void);
bool		create_socket(int *sockfd);
char		*read_request(int socketfd, int *byteRead, bool clear);

typedef struct s_online_player
{
	int		serverId;
	char	playerName[SV_MAX_PLAYER_NAME + 1]; // forbiddenChars : ":;,"
	t_vec3	pos;
	int		health;
}	t_online_player;

t_online_player	*get_player_from_source(t_list *players, int player_src);
t_online_player	*create_online_player(t_list **players, int server_id);

enum e_server_status
{
	UNINITIALIZED,
	CONNECTED,
	DISCONNECTED,
	ERR_INVALID_ADDRESS,
	ERR_CREATE_SOCKET,
	ERR_FAILED_CONNEXION,
};

typedef struct s_server
{
	// server informations
	char					ip[16];
	char					port_str[6];
	char					playerName[SV_MAX_PLAYER_NAME + 1];
	uint16_t				port;
	enum e_server_status	status;
	t_list					*online_player;

	// server connexion data: internal managment only
	struct sockaddr_in		addr;
	int						sockfd;

}	t_server;

void	manage_server_request(t_server *srv, char *request, void *mlx);

typedef void (*t_req_action_fct)(t_server *, char *, void *);
void	receive_message(t_server *srv, char *value, void *mlx);
void	player_disconnect(t_server *srv, char *value, void *mlx);
void	set_player_attr(t_server *srv, char *value, void *mlx);
void	set_player_pos(t_server *srv, char *value, void *mlx);
void	set_player_health(t_server *srv, char *value, void *mlx);
void	set_door_state(t_server *srv, char *value, void *mlx);
void	act_shoot(t_server *srv, char *value, void *mlx);
void	act_cut(t_server *srv, char *value, void *mlx);

void	connect_to_server(t_server *srv);
void	print_network_err(enum e_server_status status);
bool	client_loop_hook(t_server *srv, void *mlx);
void	close_server(t_server *srv, enum e_server_status status);

#endif