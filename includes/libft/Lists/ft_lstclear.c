/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:24:23 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/06 10:47:37 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*plist;

	if (lst == NULL || del == NULL)
		return ;
	list = *lst;
	while (list != NULL)
	{
		del(list->content);
		plist = list;
		list = list->next;
		free(plist);
	}
	*lst = NULL;
}
