/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:41:04 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/21 16:57:11 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;
	int		i;
	char	*ptr;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	ptr = (char *)s;
	while (ptr[len] != '\0')
		len++;
	dest = (char *)malloc(len + 1);
	if (!(dest))
		return (NULL);
	while (ptr[i] != '\0')
	{
		dest[i] = ptr[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
