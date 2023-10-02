/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:00 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/29 12:32:50 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

// Builtin version of export

void	bt_export(void)
{
	t_tokens	*args;
	t_tokens	*env;
	char		*str;

	env = t()->env;
	args = ex()->exec;
	if (args->next)
	{
		while (args->next)
		{
			args = args->next;
			str = ft_strdup(args->data->str);
			if (!str)
			{
				ft_putendl_fd("Error: Malloc failed", 2);
				return ;
			}
			if (!ft_env_replace(env, str))
				env = ft_lstadd_back(env, ft_lstnew(get_data(str, WORD)));
			else
				ft_free_str(str);
		}
	}
	else
		ft_print_env(env);
}

// Builtin version of unset

void	bt_unset(void)
{
	t_tokens	*args;
	t_tokens	*env;
	t_tokens	*head;
	size_t		i;

	args = ex()->exec->next;
	while (args)
	{
		i = 0;
		while (args->data->str[i] && args->data->str[i] != '=')
			i++;
		if (!args->data->str[i])
		{
			env = t()->env;
			head = env;
			unset(env, head, args);
		}
		else
		{
			ft_putstr_fd(args->data->str, 2);
			ft_putendl_fd(" : not a valid identifier", 2);
		}
		args = args->next;
	}
}

// Builtin version of env

void	bt_env(void)
{
	t_tokens	*env;
	size_t		i;

	env = t()->env;
	while (env)
	{
		i = 0;
		while (env->data->str[i])
		{
			if (env->data->str[i] == '=')
			{
				printf ("%s\n", env->data->str);
				break ;
			}
			i++;
		}
		env = env->next;
	}
}
