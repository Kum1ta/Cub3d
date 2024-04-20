/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:24:23 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/20 15:25:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*plist;

	if (lst == NULL)
		return ;
	list = *lst;
	while (list != NULL)
	{
		if (del != NULL)
			del(list->content);
		plist = list;
		list = list->next;
		free(plist);
	}
	*lst = NULL;
}
