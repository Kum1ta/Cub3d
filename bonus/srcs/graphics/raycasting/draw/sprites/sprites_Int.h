/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:16:18 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:11:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_INT_H
# define SPRITES_INT_H

# include "../../raycasting.h"

typedef struct s_drawsprt_attr
{
	int	start_x;
	int	start_y;
	int	pos_x;
	int	pos_y;
	int	img_pos_x;
	int	img_pos_y;
}	t_drawsprt_attr;

t_sprite	*get_sprite_list(t_mlx *mlx);
void		set_sprites_screen_x(t_sprite *sprites, t_vec3 plyPos, t_mlx *mlx);
void		set_sprite_img(t_mlx *mlx, t_sprite *sprite);
bool		draw_sprite(t_mlx *mlx, t_sprite *sprite, t_raydata **ray);

#endif