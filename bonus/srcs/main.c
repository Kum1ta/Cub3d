/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/09 16:29:51 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*argument_map(void *ptr, int action);

int	main(int ac, char **av)
{
	t_settings	*settings;
	t_map		*map;

	(void)ac;
	settings = parse_config_file(".config");
	map = parse_map(av[1]);
	if (!map)
		return (0);
	argument_map(av[1], -1);
	graphics_part(map, settings);
}
