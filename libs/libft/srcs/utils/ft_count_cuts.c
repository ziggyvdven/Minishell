/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_cuts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:13 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/15 11:48:36 by zvandeven        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//functions that count how many cuts there have to be given a certain delimiter

int	ft_count_cuts(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (str[0] != c)
		count = 1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			count++;
			i++;
			while (str[i] && (!ft_iswspace(str[i]) && str[i] != c))
				i++;
			if (!str[i])
				break ;
			count++;
		}
	}
	return (count);
}
