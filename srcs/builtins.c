/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/10/04 16:06:12 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// buildin version of echo with the -n flag

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

// Builtin version of cd

void	bt_cd(void)
{
	DIR		*dir;
	char	*path;

	if (!ex()->exec->next || ex()->exec->next->data->str[0] == '~')
		path = ft_get_env("HOME");
	else
		path = ft_strdup(ex()->exec->next->data->str);
	dir = opendir (path);
	if (!dir)
	{
		perror (path);
		ex()->exitcode = 1;
	}
	else
	{
		change_pwd("old");
		chdir (path);
		closedir (dir);
		ex()->exitcode = 0;
		change_pwd("new");
	}
	ft_free_str(path);
}

// Builtin version of pwd

void	bt_pwd(void)
{
	char	*pwd;

	pwd = getcwd (NULL, 0);
	printf ("%s\n", pwd);
	ft_free_str(pwd);
	ex()->exitcode = 0;
}

// Builtin version of exit. exits with given exit code

void	bt_exit(void)
{
	t_tokens	*bt;
	int			i;

	bt = ex()->exec->next;
	if (bt)
	{
		i = ft_atoi(bt->data->str);
		if (!ft_hasdigit(bt->data->str))
		{
			exits();
			ft_putstr_exit("exit: numeric argument required\n", 1, 255);
		}
		else
		{
			exits();
			ft_putstr_exit("exit\n", 1, i);
		}
	}
	exits();
	ft_putstr_exit("exit\n", 1, ex()->exitcode);
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
