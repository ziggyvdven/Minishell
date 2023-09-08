/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:50:23 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/08 12:57:18 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_printlst(t_tokens *map_lst)
{
	t_tokens	*ptr;

	ptr = map_lst;
	// ft_printf("map:\n");
	while (ptr != NULL)
	{
		ft_printf("%s\n", ptr->data->str);
		ptr = ptr->next;
	}
	ft_printf("\n");
}
