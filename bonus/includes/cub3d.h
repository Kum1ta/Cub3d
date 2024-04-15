/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:58:17 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 21:41:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "vector.h"
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <SDL2/SDL.h>

typedef struct s_mlx t_mlx;

enum e_blocktype {
	EMPTY,
	END,
	WALL,
	DOOR,
	FLOOR
};

union u_blockdata {
	bool	door;
	int		wall;
};


typedef struct s_block {
	enum e_blocktype	type;
	union u_blockdata	data;
}	t_block;

typedef struct s_texture {
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_map {
	t_block		**blocks;
	size_t		width;
	size_t		height;

	t_texture	texture;
	t_vec3		playerPos;
	t_vec3		camDir;
	t_vec2		camPlane;
}	t_map;

typedef struct s_settings {
	int		width;
	int		height;
	int		quality;
	int		antialiasing;
	int		show_minimap;
	int		minimap_pos;
	int		minimap_pos_x;
	int		minimap_pos_y;
	int		show_fps;
}	t_settings;

/* --- main_graphics.c ----------------------------------------------------- */
void		graphics_part(t_map *map, t_settings *settings);

/* --- parse_file.c -------------------------------------------------------- */
t_map		*parse_map(char *filename, int screen_resol[2]);

/* --- free_map.c ---------------------------------------------------------- */
void		free_blocks(t_block **blocks);
void		free_map(t_map *map);

/* --- utils.c ------------------------------------------------------------- */
void		put_fps(t_mlx *mlx, int need_free);
void		*error_ptr(char *str, void *ret);
int			error_int(char *str, int ret);
void		wait_us(long long time_us);
long long	get_now_time(void);

/* --- config_main.c ------------------------------------------------------- */
t_settings	*parse_config_file(char *path);

#endif