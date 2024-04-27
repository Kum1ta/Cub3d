/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:12:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"

void	put_fps(t_mlx *mlx, int need_free)
{
	static long long	last_time = 0;
	static int			change = 0;
	long long			now;
	float				fps;
	static char			tmp[4];

	if (need_free || mlx->stg->show_fps == 0)
		return ;
	now = get_now_time();
	fps = 1000000 / (now - last_time);
	last_time = now;
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 20.0f);
	if (change % 10 == 0)
	{
		tmp[0] = (int)fps / 100 % 10 + '0';
		tmp[1] = (int)fps / 10 % 10 + '0';
		tmp[2] = (int)fps % 10 + '0';
		tmp[3] = '\0';
		change = 0;
	}
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 55,
		15, 0xFFFF0000, tmp);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
	change++;
}

void	*error_ptr(char *str, void *ret)
{
	ft_printf("Cube3d: %s\n", str);
	return (ret);
}

int	error_int(char *str, int ret)
{
	ft_printf("Cube3d: %s\n", str);
	return (ret);
}

void	wait_us(long long time_us)
{
	struct timeval	tv;
	long long		time;
	long long		time2;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec + time_us;
	time2 = 0;
	while (time2 < time)
	{
		gettimeofday(&tv, NULL);
		time2 = tv.tv_sec * 1000000 + tv.tv_usec;
	}
}

long long	get_now_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
