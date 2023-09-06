/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:57:50 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/06/15 11:52:12 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_printmap(char **map)
{
	int	i;

	i = -1;
	ft_printf("map:\n");
	while (map[++i] != NULL)
		ft_printf("%s\n", map[i]);
	ft_printf("\n");
}
