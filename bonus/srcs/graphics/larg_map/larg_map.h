/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:18:26 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LARG_MAP_H
# define LARG_MAP_H

# include "../graphics.h"

/* ---- larg_map.c ---------------------------------------------------------- */
void	add_button_lm(t_mlx *mlx, int xy[2], void *img,
			char *(*f)(void *, int));
void	change_config_file_lm(t_settings_window *stg);

/* ---- settings.c ---------------------------------------------------------- */
void	fill_image(t_mlx *mlx, void *img, int color, int xy[2]);
void	init_bg(t_mlx *mlx, t_img *bg, void **bg_word);
void	put_button(t_mlx *mlx, int diff, t_img bg);
void	options_menu_lm(t_mlx *mlx, int need_free);
void	down_bar(t_mlx *mlx, int need_free);

/* ---- list_button.c ------------------------------------------------------- */
int		add_case_lm(t_mlx *mlx, int pos[4], char *str, int list[3]);
void	list_button_quality_lm(t_mlx *mlx, int xy[2]);
void	list_button_texture_lm(t_mlx *mlx, int xy[2]);
void	list_button_fps_lm(t_mlx *mlx, int xy[2]);
void	list_button_aa_lm(t_mlx *mlx, int xy[2]);

/* ---- sensibility.c ------------------------------------------------------- */
void	btn_scroll(t_mlx *mlx, int x, int y, int *edit_value);

/* ---- init.c -------------------------------------------------------------- */
void	init_button_lm(t_mlx *mlx, t_selected (*selected)[22], int *init);
void	init_antialiasing(t_mlx *mlx, t_selected (*selected)[22]);

/* ---- button_action.c ----------------------------------------------------- */
void	not_selected_button_lm(t_mlx *mlx, t_selected selected[22],
			int xy[2], int list[3]);
char	*button_resume_lm(void *mlx_raw, int action);
char	*button_option_lm(void *mlx, int action);
char	*main_menu_lm(void *mlxRaw, int action);
char	*button_main_lm(void *mlx, int action);

/* ---- draw_map.c ---------------------------------------------------------- */
void	draw_square(t_mlx *mlx, int size, int color, int xy[2]);
void	put_player(t_mlx *mlx);
void	fill_map(t_mlx *mlx);

#endif