/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_timestamp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:06 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 09:37:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		res;

	gettimeofday(&te, 0);
	res = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (res);
}
