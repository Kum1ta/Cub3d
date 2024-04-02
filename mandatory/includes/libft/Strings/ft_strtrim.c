/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:30:26 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/06 10:27:39 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_a_sep(char c, const char *sep)
{
	unsigned int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

static int	trimmed_strlen(char const *s1, char const *set, int *i, int *j)
{
	int	min;
	int	max;

	min = 0;
	while (s1[min] && is_a_sep(s1[min], set))
		min++;
	max = ft_strlen(s1) - 1;
	while (max > min && is_a_sep(s1[max], set))
		max--;
	max++;
	*i = min;
	*j = max;
	return (max - min);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		min;
	int		max;
	int		i;

	if (s1 == NULL)
		return (0);
	str = malloc((trimmed_strlen(s1, set, &min, &max) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (min + i != max)
	{
		str[i] = s1[min + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
