/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:02:12 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 17:23:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static inline int	is_sep(const char *s, int i, char *skip)
{
	if (i != 0 && s[i - 1] == '\\' && (i == 1 || s[i - 2] != '\\'))
		return (0);
	return (ft_strchr(skip, s[i]) != NULL);
}

static int	ft_get_nb_words(char const *s, char *skip)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(s, i, skip))
		{
			if (i == 0 || is_sep(s, i - 1, skip))
				nb++;
		}
		i++;
	}
	return (nb);
}

static int	ft_wordlen(char const *s, char *skip)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_sep(s, i, skip))
		i++;
	return (i);
}

static char	**ft_fill_res(char const *s, char *skip, char **res)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (!is_sep(s, i, skip))
		{
			if (i == 0 || is_sep(s, i - 1, skip))
			{
				res[j] = ft_calloc((ft_wordlen(s + i, skip) + 1), sizeof(char));
				if (res[j++] == NULL)
				{
					free_split(res, 0);
					return (NULL);
				}
				k = 0;
			}
			if (s[i] != '\\' || (i != 0 && s[i - 1] == '\\'))
				res[j - 1][k++] = s[i];
		}
	}
	return (res);
}

char	**ft_split2(char const *s, char *skip)
{
	char	**res;
	size_t	nb_words;

	if (s == NULL)
		return (NULL);
	nb_words = ft_get_nb_words(s, skip);
	if (nb_words == 0)
	{
		res = malloc(sizeof(char *));
		res[0] = 0;
		return (res);
	}
	res = ft_calloc((nb_words + 1), sizeof(char *));
	if (res == NULL)
		return (res);
	return (ft_fill_res(s, skip, res));
}
