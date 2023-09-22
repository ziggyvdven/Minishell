/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_cuts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:13 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/22 12:00:35 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

bool	is_meta_libft(char c)
{
	if (c)
		if (c == '"' || c == '|' || c == '<' || c == '>' || c == 39 
			|| c == '-' || c == '$')
			return (true);
	return (false);
}

//functions that count how many cuts there have to be given a certain delimiter

int	ft_count_cuts(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c) 
		{
			i++;
			if (str[i] == c)
				i++;
			else if (str[i] && !ft_iswspace(str[i]) && !is_meta_libft(str[i]))
				while (str[i] && !ft_iswspace(str[i])
					&& str[i] != c && !is_meta_libft(str[i]))
					i++;
		}
		else
			while (str[i] && str[i] != c)
				i++;
		count++;
	}
	return (count);
}
