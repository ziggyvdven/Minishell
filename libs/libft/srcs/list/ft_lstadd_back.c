/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:49:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/08 12:43:10 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_tokens	*ft_lstadd_back(t_tokens *lst, t_tokens *new)
{
	t_tokens	*ptr;

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
