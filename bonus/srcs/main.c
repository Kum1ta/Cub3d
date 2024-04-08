/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/08 17:46:45 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*argument_map(void *ptr, int action);

int	main(int ac, char **av)
{
	t_map	*map;

	(void)ac;
	map = parse_map(av[1]);
	if (!map)
		return (0);
	argument_map(av[1], -1);
	graphics_part(map);
}
