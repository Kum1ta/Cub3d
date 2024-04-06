/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_network_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:14:16 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 10:22:04 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_connexion.h"

void	print_network_err(enum e_server_status status)
{
	if (status == ERR_INVALID_ADDRESS)
		ft_dprintf(2, "Failed to connect to server: Invalid address.\n");
	else if (status == ERR_CREATE_SOCKET)
		ft_dprintf(2, "Failed to create socket connexion to server.\n");
	else if (status == ERR_FAILED_CONNEXION)
		ft_dprintf(2, "Failed to connect to server : %s.\n", strerror(errno));
}
