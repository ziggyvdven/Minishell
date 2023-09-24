/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:24:36 by oroy              #+#    #+#             */
/*   Updated: 2023/09/24 12:47:43 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(char **envp)
{
	t_tokens	*env;
	size_t		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env = ft_lstadd_back(env, ft_lstnew(get_data(envp[i], WORD)));
		i++;
	}
	t()->env = env;
}
