/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:57:55 by psalame           #+#    #+#             */
/*   Updated: 2024/04/13 16:11:49 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>

typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

float	get_distance_between_2dcoords(t_vec3 pos1, t_vec3 pos2);
t_vec3	parse_vec3(char **strPtr);
t_vec2	parse_vec2(char **strPtr);


#endif