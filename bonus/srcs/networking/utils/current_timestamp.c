/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_timestamp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:06 by psalame           #+#    #+#             */
/*   Updated: 2024/03/20 16:19:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>

long long current_timestamp() {
	struct timeval te; 
	gettimeofday(&te, 0);
	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
	return milliseconds;
}
