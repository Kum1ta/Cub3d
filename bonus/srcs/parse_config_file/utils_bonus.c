/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:42:54 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 23:46:04 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

int	ft_atoi_s(const char *str)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		nbr = nbr * 10 + (str[i] - 48);
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	return (nbr);
}

int	is_not_digit(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

void	*error_config(char *msg, void *ptr)
{
	write(2, "\033[1;31m[ERROR]\033[0m ", 20);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(ptr);
	return (NULL);
}

t_settings	*free_func(char *line, int fd, t_settings *settings)
{
	free(line);
	close(fd);
	return (error_config("Error in config file", settings));
}
