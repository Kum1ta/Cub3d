/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:58:17 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/13 15:31:36 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_block {
	WALL,
	FLOOR,
	EMPTY,
	END
}	t_block;

typedef struct s_texture {
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
	float	h;
}	t_vec3;

typedef struct s_map {
	t_block		**blocks;
	
	t_texture	texture;
	t_vec3		playerPos;
}	t_map;

void	graphics_part(t_block map[30][100]);

#endif