/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:57:50 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/14 15:37:04 by zvandeven        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_printmap(char **map)
{
	int	i;

	i = -1;
	ft_printf("map:\n");
	while (map[++i] != NULL)
		ft_printf("arr[%d] = %s\n", i, map[i]);
	ft_printf("\n");
}
