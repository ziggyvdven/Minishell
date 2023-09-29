/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:24:36 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 13:46:21 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Getenv function for minishell environement 

char	*ft_get_env(char *str)
{
	t_tokens	*env;
	char		*s;
	size_t		i;

	env = t()->env;
	s = NULL;
	if (!str)
		return (NULL);
	while (env != NULL)
	{
		i = 0;
		while (env->data->str[i] != '=' && env->data->str[i])
			i++;
		if (ft_strnstr(env->data->str, str, ft_strlen(str))
			&& ft_strlen(str) == i)
			s = ft_substr(env->data->str, ft_strlen(str) + 1,
					ft_strlen(env->data->str) - ft_strlen(str) + 1);
		env = env->next;
	}
	return (s);
}

// stores environement in linked list

void	set_env(char **envp)
{
	t_tokens	*env;
	size_t		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env = ft_lstadd_back(env,
				ft_lstnew(get_data(ft_strdup(envp[i]), WORD)));
		i++;
	}
	t()->env = env;
}
