/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:49:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/24 12:15:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_tokens	*ft_lstadd_back(t_tokens *lst, t_tokens *new)
{
	t_tokens	*ptr;

	if (lst == NULL)
		lst = new;
	else
	{
		ptr = lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (lst);
}
