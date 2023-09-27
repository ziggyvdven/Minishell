/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/27 16:07:16 by zvan-de-         ###   ########.fr       */
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

	pwd = getcwd(NULL, 0);
	printf ("%s\n", pwd);
	ft_free_str(pwd);
}

void	bt_env(void)
{
	t_tokens	*env;

	env = t()->env;
	while (env)
	{
		printf ("%s\n", env->data->str);
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
				ft_putstr_exit("Error: Malloc failed", 2, 1);
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
	t_tokens	*env;
	t_tokens	*head;
	char		*str;
	size_t		len;

	if (ex()->exec->next)
	{
		str = ex()->exec->next->data->str;
		len = ft_strlen(str);
		env = t()->env;
		head = env;
		while (env)
		{
			if (!ft_strncmp(env->data->str, str, len) && env->data->str[len] == '=')
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
}
void	bt_exit(void)
{
	ft_putstr_exit("exit\n", 1, 0);
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
	else if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "exit", 4))
		bt_exit();
	else
		status = false;
	return (status);
}
