/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/17 14:48:08 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"

void	put_fps(t_mlx *mlx, int need_free)
{
	static long long	last_time = 0;
	static int			change = 0;
	long long			now;
	float				fps;
	static char			*tmp = NULL;

	if (need_free)
	{
		free(tmp);
		return ;
	}
	now = get_now_time();
	fps = 1000000 / (now - last_time);
	last_time = now;
	if (change % 10 == 0)
	{
		if (tmp)
			free(tmp);
		tmp = ft_itoa(fps);
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 25, 15, 0xFFFF0000, tmp);
		change = 0;
	}
	else
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 25, 15, 0xFFFF0000, tmp);
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

	static int	i = 0;
	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"wait_us()\" : Forbidden function\n\033[0m");
		i++;
	}

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

	static int	i = 0;
	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"get_now_time()\" : Forbidden function\n\033[0m");
		i++;
	}

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
