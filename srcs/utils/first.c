/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 23:24:05 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
