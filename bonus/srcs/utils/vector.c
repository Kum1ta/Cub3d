/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:14:58 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 19:41:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

float	get_distance_between_2dcoords(t_vec3 pos1, t_vec3 pos2)
{
	return (sqrtf(powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2)));
}

t_vec3	parse_vec3(char **strPtr)
{
	t_vec3	res;
	char	*str;

	str = *strPtr;
	res.x = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.y = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.z = ft_atof(str);
	while (*str && *str++ != ',')
		;
	*strPtr = str;
	return (res);
}

t_vec2	parse_vec2(char **strPtr)
{
	t_vec2	res;
	char	*str;

	str = *strPtr;
	res.x = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.y = ft_atof(str);
	while (*str && *str++ != ',')
		;
	*strPtr = str;
	return (res);
}
