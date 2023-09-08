/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:49 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/08 12:34:29 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstdelone(t_tokens *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->str);
	free(lst);
	return ;
}
