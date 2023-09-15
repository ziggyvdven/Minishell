/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:49 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/12 22:27:53 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstdelone_bck(t_tokens *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->str);
	free(lst);
	return ;
}
