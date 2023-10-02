/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_ar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:22:00 by olivierroy        #+#    #+#             */
/*   Updated: 2023/10/02 12:45:48 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_cmd_ar(void)
{
	t_tokens	*ptr;
	char		**cmd;
	int			count;
	int			i;

	i = 0;
	ptr = ex()->exec;
	count = ft_lstsize(ptr);
	cmd = ft_calloc(count + 1, sizeof (char *));
	if (!cmd)
		exit (exec_error("Malloc error", 1));
	while (i < count)
	{
		cmd[i] = ft_calloc(ft_strlen(ptr->data->str), sizeof (char));
		if (!cmd[i])
		{
			ft_free_ar(cmd);
			exit (exec_error("Malloc error", 1));
		}
		cmd[i] = ft_strdup(ptr->data->str);
		ptr = ptr->next;
		i++;
	}
	cmd[i] = NULL;
	ex()->cmd = cmd;
}
