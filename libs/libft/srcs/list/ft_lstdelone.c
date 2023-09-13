/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:49 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/12 22:28:41 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstdelone(t_tokens *lst)
{
	if (!lst)
		return ;
	// (*del)(lst->str);
	free(lst);
	return ;
}
