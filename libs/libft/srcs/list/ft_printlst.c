/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:50:23 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/11 13:39:28 by zvandeven        ###   ########.fr       */
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
		ft_printf("%i\n\n", ptr->data->token_id);
		ptr = ptr->next;
	}
}
