/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/27 16:34:36 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bt_echo(void)
{
	t_tokens	*bt;
	int			newline;

	newline = 1;
	bt = ex()->exec->next;
	if (bt)
	{
		if (!ft_strncmp(bt->data->str, "-n", 2))
		{
			newline = 0;
			bt = bt->next;
		}
		while (bt)
		{
			printf ("%s", bt->data->str);
			bt = bt->next;
			if (bt)
				printf (" ");
		}
	}
	if (newline)
		printf ("\n");
	ex()->exitcode = 0;
}

void	bt_cd(void)
{
	DIR		*dir;
	char	*path;

	if (!ex()->exec->next)
		return ;
	path = ex()->exec->next->data->str;
	dir = opendir (path);
	if (!dir)
	{
		perror (path);
		ex()->exitcode = 1;
	}
	else
	{
		chdir (path);
		closedir (dir);
	}
}

void	bt_pwd(void)
{
	char	*pwd;

	pwd = getcwd (NULL, 0);
	printf ("%s\n", pwd);
	ft_free_str(pwd);
}

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
			env = ft_lstadd_back(env, ft_lstnew(get_data(str, WORD)));
		}
	}
	else
	{
		printf ("Print everything");
	}
}

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
			while (env)
			{
				if (!ft_strncmp(args->data->str, env->data->str, i))
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
		}
		else
		{
			ft_putstr_fd(args->data->str, 2);
			ft_putendl_fd(" : not a valid identifier", 2);
		}
		args = args->next;
	}
}

bool	is_builtin(char *cmd)
{
	int	status;

	status = true;
	if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "echo", 4))
		bt_echo();
	else if (ft_strlen(cmd) == 2 && !ft_strncmp(cmd, "cd", 2))
		bt_cd();
	else if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "pwd", 3))
		bt_pwd();
	else if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
		bt_export();
	else if (ft_strlen(cmd) == 5 && !ft_strncmp(cmd, "unset", 5))
		bt_unset();
	else if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "env", 3))
		bt_env();
	// else if (cmd == "exit")
	// 	printf ("Do exit()");
	else
		status = false;
	return (status);
}
