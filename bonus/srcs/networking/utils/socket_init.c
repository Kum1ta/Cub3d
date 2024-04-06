/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:20 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 13:46:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <stdbool.h>
#include <asm-generic/socket.h>

bool	create_socket(int *sockfd)
{
	int	opt;
	int	sock_flags;

	*sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (*sockfd == -1)
		return (false);
	opt = 1;
	sock_flags = SO_REUSEADDR | SO_REUSEPORT;
	if (setsockopt(*sockfd, SOL_SOCKET, sock_flags, &opt, sizeof(opt)))
		return (false);
	return (true);
}