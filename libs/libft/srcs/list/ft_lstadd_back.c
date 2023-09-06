/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:49:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/05/18 14:45:51 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_node	*ft_lstadd_back(t_node *lst, t_node *new)
{
	t_node	*ptr;

	if (!lst)
		return (NULL);
	if (lst)
	{
		if (lst == NULL)
			lst = new;
		else
		{
			ptr = lst;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
	return (lst);
}
