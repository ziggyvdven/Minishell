/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:49 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/21 11:03:38 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstdelone(t_tokens *lst)
{
	if (!lst)
		return ;
	ft_free_str(lst->data->str);
	free(lst->data);
	lst->data = NULL;
	free(lst);
	lst = NULL;
	return ;
}

void	ft_lstdelone2(t_tokens *lst)
{
	if (!lst)
		return ;
	free(lst);
	lst = NULL;
	return ;
}
