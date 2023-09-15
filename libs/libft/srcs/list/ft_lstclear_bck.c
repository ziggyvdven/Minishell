/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:07:11 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/12 22:27:59 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear_bck(t_tokens **lst, void (*del)(void *))
{
	t_tokens	*temp;

	if (!*lst || !lst || !del)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	return ;
}
