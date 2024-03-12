/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:04:44 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 13:05:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 7 && c <= 13));
}
