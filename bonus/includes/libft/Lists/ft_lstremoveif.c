/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:03:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/05 18:58:37 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstremoveif(t_list **lst, void *ele, void (*del)(), int (*cmp)())
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	if (!lst || !cmp)
		return ;
	prev = NULL;
	current = *lst;
	while (current)
	{
		next = current->next;
		if ((*cmp)(current->content, ele) == 0)
		{
			if (prev == NULL)
				*lst = next;
			else
				prev->next = next;
			ft_lstdelone(current, del);
			current = next;
		}
		else
			prev = current;
		current = next;
	}
}
