/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:27:02 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/21 13:14:44 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_ar(char **ar)
{
	size_t	i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		ar[i] = NULL;
		i++;
	}
	free(ar);
	ar = NULL;
}

void	ft_free_n_ar(char **ar, int n)
{
	size_t	i;

	if (!ar)
		return ;
	i = 0;
	while (i < n)
	{
		if (ar[i])
		{
			free(ar[i]);
			ar[i] = NULL;
		}
		i++;
	}
	free(ar);
	ar = NULL;
}
