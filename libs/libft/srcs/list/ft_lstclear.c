/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:07:11 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/20 17:18:31 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_tokens **lst)
{
	t_tokens	*temp;

	if (!*lst || !lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = temp;
	}
	return ;
}

void	ft_clearlst(t_tokens **lst)
{
	t_tokens	*temp;

	if (!*lst || !lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	return ;
}
