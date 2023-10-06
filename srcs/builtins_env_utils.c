/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:49:06 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/10/06 11:01:17 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// prints env when export is executed

void	ft_print_env(t_tokens *env)
{
	t_tokens	*ptr;
	int			i;

	ptr = env;
	while (ptr != NULL)
	{
		i = -1;
		if (ft_strchr(ptr->data->str, '='))
		{
			ft_printf("declare -x ");
			while (ptr->data->str[++i] != '=')
				ft_putchar(ptr->data->str[i]);
			if (ptr->data->str[i])
			{
				ft_putchar('=');
				i++;
			}
			ft_putchar(34);
			while (ptr->data->str[i])
				ft_putchar(ptr->data->str[i++]);
			ft_putchar(34);
			ft_putchar('\n');
		}
		ptr = ptr->next;
	}
}

// replaces string at given pointer

int	replace(char *s, char *str, t_tokens *ptr)
{
	size_t	i;

	i = 0;
	while (ptr->data->str[i] && ptr->data->str[i] != '=')
		i++;
	if (ft_strnstr(ptr->data->str, s, ft_strlen(s)) && ft_strlen(s) == i)
	{
		ft_free_str(ptr->data->str);
		ptr->data->str = ft_strdup(str);
		ft_free_str(s);
		return (1);
	}
	return (0);
}

//Checks if variable exist and replaces if it does

int	ft_env_replace(t_tokens *env, char *str)
{
	char		*s;
	t_tokens	*ptr;
	size_t		i;

	i = -1;
	if (!str || !env)
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (ft_putstr_excode(
					"Minishell: export: not a valid identifier\n", 2, 1));
	}
	if (str[i] != '=')
		return (0);
	s = ft_substr(str, 0, i);
	ptr = env;
	while (ptr != NULL)
	{
		if (replace(s, str, ptr))
			return (1);
		ptr = ptr->next;
	}
	ft_free_str(s);
	return (0);
}

//removes node from linked list.

int	unset(t_tokens	*env, t_tokens	*head, t_tokens	*args)
{
	size_t	j;

	while (env)
	{
		j = 0;
		while (env->data->str[j] != '=')
			j++;
		if (!ft_strncmp(args->data->str, env->data->str, j) 
			&& ft_strlen(args->data->str) == j)
		{
			if (head == env)
				t()->env = env->next;
			else
				head->next = env->next;
			ft_lstdelone(env);
			break ;
		}
		head = env;
		env = env->next;
	}
	return (0);
}

// Update PWD and OLDPWD after cd command

void	change_pwd(char *s)
{
	char	*pwd;
	char	*str;

	pwd = getcwd (NULL, 0);
	if (!pwd && !ft_strncmp(s, "old", 3))
		pwd = ft_get_env("PWD");
	if (!ft_strncmp(s, "old", 3))
		str = ft_strjoin("OLDPWD=", pwd);
	else
		str = ft_strjoin("PWD=", pwd);
	ft_free_str(pwd);
	ft_env_replace(t()->env, str);
	ft_free_str(str);
}
