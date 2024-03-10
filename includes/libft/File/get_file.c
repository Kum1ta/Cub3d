/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:07:50 by edbernar          #+#    #+#             */
/*   Updated: 2023/12/19 00:51:37 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strjoin_get_fil_ver(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((i + 2) * sizeof(char));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && s2[++j])
		str[i + j] = s2[j];
	str[i + j] = 0;
	if (s1 != NULL)
		free(s1);
	return (str);
}

char	*get_file(char *file)
{
	char	*buffer;
	char	*str;
	int		fd;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = malloc(100001 * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	str = NULL;
	while (1)
	{
		ret = read(fd, buffer, 100000);
		if (ret == 0)
			break ;
		buffer[ret] = 0;
		str = ft_strjoin_get_fil_ver(str, buffer);
		if (str == NULL)
			break ;
	}
	free(buffer);
	return (str);
}
