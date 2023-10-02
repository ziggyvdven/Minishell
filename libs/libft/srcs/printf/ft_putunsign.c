/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:37:19 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/29 13:49:23 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_ucheckzero(long int a)
{
	if (a == 0)
	{
		write (1, "0", 1);
	}
}

int	ft_ucount(unsigned int n)
{
	long unsigned int	tempn;
	unsigned int		count;

	tempn = n;
	count = 0;
	if (n == 0)
		count++;
	while (tempn > 0)
	{
		tempn = tempn / 10;
		count++;
	}
	return (count - 1);
}

int	ft_putunsing(unsigned int n, int count)
{
	char				str[11];
	long unsigned int	tempn;
	int					i;

	i = 1;
	tempn = n;
	ft_ucheckzero(tempn);
	while (tempn > 0)
	{
		str[i++] = tempn % 10 + 48;
		tempn = tempn / 10;
	}
	i = i -1;
	while (i > 0)
	{
		write (1, &str[i], 1);
		--i;
	}
	count = ft_ucount(n);
	return (count);
}
