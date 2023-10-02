/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hasalpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:51:13 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/28 11:10:56 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

bool	ft_hasalpha(char *s)
{
	unsigned int	i;

	if (!s)
		return (false);
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalpha(s[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	ft_hasdigit(char *s)
{
	unsigned int	i;

	if (!s)
		return (false);
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			return (true);
		i++;
	}
	return (false);
}

// int main()
// {
// 	char s[] = "1asdgahdsjgfjd-=-==";

// 	if (ft_hasdigit(s))
// 		printf("Has digit");
// 	else
// 		printf("no digit");
// }
