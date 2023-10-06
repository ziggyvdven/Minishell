/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:24:36 by oroy              #+#    #+#             */
/*   Updated: 2023/10/06 11:33:49 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_env_ar(void)
{
	char		**arr;
	t_tokens	*env;
	size_t		i;

	i = 0;
	env = t()->env;
	arr = ft_calloc(ft_lstsize(env) + 1, sizeof (char *));
	if (!arr)
		exit (exec_error("Malloc error", 1));
	t()->env_arr = arr;
	while (env)
	{
		t()->env_arr[i] = ft_strdup(env->data->str);
		if (!t()->env_arr[i])
			exit (exec_error("Malloc error", 1));
		env = env->next;
		i++;
	}
	t()->env_arr[i] = NULL;
}

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
	char		*str;
	char		*new_num;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env = ft_lstadd_back(env,
				ft_lstnew(get_data(ft_strdup(envp[i]), WORD)));
		i++;
	}
	t()->env = env;
	str = ft_get_env("SHLVL");
	i = ft_atoi(str);
	i++;
	ft_free_str(str);
	new_num = ft_itoa(i);
	str = ft_strjoin("SHLVL=", new_num);
	ft_free_str(new_num);
	ft_env_replace(t()->env, str);
	ft_free_str(str);
}
