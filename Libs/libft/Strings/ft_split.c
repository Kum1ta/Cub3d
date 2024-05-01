/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:02:12 by edbernar          #+#    #+#             */
/*   Updated: 2023/12/02 01:25:20 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	word_len(const char *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (word);
		word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word);
}

static int	ft_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	free_split(char **strf, int error)
{
	int	i;

	i = 0;
	if (error)
		ft_putendl_fd("Error.", 2);
	while (strf[i])
	{
		free(strf[i]);
		i++;
	}
	free(strf);
}

void	fill(char **strf, const char *s, char c)
{
	int		k;
	int		j;
	int		i;

	k = -1;
	i = 0;
	while (++k < word_len(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return ;
		strf[k] = malloc((ft_len((char *)&s[i], c) + 1) * sizeof(char));
		if (strf[k] == NULL)
		{
			free_split(strf, 0);
			return ;
		}
		j = -1;
		while (s[i + ++j] && s[i + j] != c)
			strf[k][j] = s[i + j];
		i += j;
		strf[k][j] = 0;
	}
	strf[k] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**strf;

	if (s == NULL)
		return (NULL);
	strf = malloc((word_len(s, c) + 1) * sizeof(char *));
	if (strf == NULL)
		return (NULL);
	fill(strf, s, c);
	return (strf);
}
