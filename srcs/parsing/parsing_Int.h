/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:02:37 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 13:28:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_map_line_type {
	LTYPE_DATA,
	LTYPE_EMPTY,
	LTYPE_MAP
}	t_map_line_type;

typedef enum e_map_error_type {
	MAP_NO_ERROR,
	MAP_ERROR_ALLOC,
	MAP_INVALID_IDENTIFIER,
}	t_map_error_type;

#endif