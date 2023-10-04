/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:00 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/10/04 15:41:20 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				ft_putstr_excode("Error: Malloc failed", 2, 1);
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

int	bt_unset(void)
{
	t_tokens	*args;
	t_tokens	*env;
	t_tokens	*head;
	size_t		i;

	args = ex()->exec->next;
	while (args)
	{
		i = -1;
		while (args && args->data->str[++i] && args->data->str[i] != '=')
		{
			if (!ft_isalnum(args->data->str[i]))
				return (ft_putstr_excode("Not a valid identifier\n", 2, 1));
		}
		if (!args->data->str[i])
		{
			env = t()->env;
			head = env;
			unset(env, head, args);
		}
		else
			return (ft_putstr_excode("Not a valid identifier\n", 2, 1));
		args = args->next;
	}
	return (0);
}

// Builtin version of env

int	bt_env(void)
{
	t_tokens	*env;
	size_t		i;
	t_tokens	*bt;

	bt = ex()->exec->next;
	if (bt)
		return (ft_putstr_excode("Too many arguments\n", 2, 1));
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
	return (0);
}
