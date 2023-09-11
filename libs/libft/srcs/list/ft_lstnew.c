/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:55:05 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/08 12:51:53 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_tokens	*ft_lstnew(t_data *data)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(new))
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

// int main(void)
// {
//     char *str = "hello world";
//     t_list *node = ft_lstnew(str);
//     if (node == NULL)
//     {
//         printf("Error: failed to create new node\n");
//         return (1);
//     }
//     printf("Node content: %s\n", (char *)node->content);
//     return (0);
// }
