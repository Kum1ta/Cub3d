/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 16:41:41 by psalame          ###   ########.fr       */
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
	map = parse_map(av[1], (int [2]){settings->width, settings->height});
	if (!map)
		return (0);
	argument_map(av[1], -1);
	graphics_part(map, settings);
}
