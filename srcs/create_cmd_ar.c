/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_ar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:22:00 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/22 19:28:48 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_cmd_ar(void)
{
	t_tokens	*ptr;
	int			count;
	int			i;

	i = 0;
	ptr = ex()->exec;
	count = ft_lstsize(ptr);
	ex()->cmd = ft_calloc(count + 1, sizeof (char *));
	if (!ex()->cmd)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	while (i < count)
	{
		ex()->cmd[i] = ft_calloc(ft_strlen(ptr->data->str), sizeof (char));
		if (!ex()->cmd[i])
		{
			ft_free_ar(ex()->cmd);
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		}
		ex()->cmd[i] = ft_strdup(ptr->data->str);
		ptr = ptr->next;
		i++;
	}
	ex()->cmd[i] = NULL;
}
