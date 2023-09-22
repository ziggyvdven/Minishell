/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_concat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:09 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/22 18:32:50 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*ft_delwspace_tokens(t_tokens *t)
{
	t_tokens	*ptr;
	t_tokens	*tmp;
	t_tokens	*prev;

	ptr = t;
	prev = NULL;
	while (ptr != NULL)
	{
		if (ptr->data->token_id == WSPACE)
		{
			tmp = ptr;
			ptr = ptr->next;
			if (prev == NULL)
				t = ptr;
			else
				prev->next = ptr;
			ft_lstdelone(tmp);
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	return (t);
}

t_tokens	*ft_concat_tokens(t_tokens *t)
{
	t_tokens	*p;
	t_tokens	*tmp;

	p = t;
	while (p != NULL)
	{
		if ((p->data->token_id >= 110 && p->data->token_id <= 114) && p->next)
		{
			if ((p->next->data->token_id >= 110
					&& p->next->data->token_id <= 114))
			{
				p->data->str = ft_strjoin_free(p->data->str,
						p->next->data->str);
				tmp = p->next->next;
				ft_lstdelone(p->next);
				p->next = tmp;
			}
			else
				p = p->next;
		}
		else
			p = p->next;
	}
	t = ft_delwspace_tokens(t);
	return (t);
}
