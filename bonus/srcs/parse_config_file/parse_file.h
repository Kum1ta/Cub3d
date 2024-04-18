/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:39:18 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 23:54:10 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include "cub3d.h"

/* ---- config_main.c ------------------------------------------------------- */
int			*return_good_int(t_settings *settings, char *line);
void		*create_default_config(char *path);

/* ---- utils.c ------------------------------------------------------------- */
t_settings	*free_func(char *line, int fd, t_settings *settings);
void		*error_config(char *msg, void *ptr);
int			ft_atoi_s(const char *str);
int			is_not_digit(char *str);

/* ---- config_parser.c ----------------------------------------------------- */
t_settings	*parse_config_line(t_settings *settings, char *line, int fd);
t_settings	*parse_config(char *path, t_settings *settings);

#endif