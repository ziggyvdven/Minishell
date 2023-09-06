/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:50:23 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/05/18 15:42:32 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_printlst(t_node *map_lst)
{
	t_node	*ptr;

	ptr = map_lst;
	ft_printf("map:\n");
	while (ptr != NULL)
	{
		ft_printf("%s", ptr->str);
		ptr = ptr->next;
	}
	ft_printf("\n");
}
